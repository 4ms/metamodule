#include "doctest.h"
#include "wav/dr_wav.h"
#include "wav/wav_file_stream.hh"
#include <array>

constexpr std::array<float, 16> wavfil{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
constexpr std::array<float, 10> wavfil2{100, 2, 3, 4, 5, 6, 7, 8, 9, 10};

constexpr std::array<int16_t, 16> wavfil_s16{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
constexpr std::array<int16_t, 10> wavfil2_s16{100, 2, 3, 4, 5, 6, 7, 8, 9, 10};

static unsigned fil_select = 1;

drwav_bool32
drwav_init_file(drwav *pWav, const char *filename, const drwav_allocation_callbacks *pAllocationCallbacks) {
	pWav->channels = 2;

	if (fil_select == 2) {
		pWav->totalPCMFrameCount = wavfil2.size() / pWav->channels;
	} else {
		pWav->totalPCMFrameCount = wavfil.size() / pWav->channels;
	}

	pWav->readCursorInPCMFrames = 0;
	pWav->fmt.blockAlign = pWav->channels * sizeof(float);
	return true;
}

drwav_result drwav_uninit(drwav *pWav) {
	return 1;
}

drwav_uint64 drwav_read_pcm_frames_f32(drwav *pWav, drwav_uint64 framesToRead, float *pBufferOut) {

	drwav_uint64 numRead = 0;

	while (framesToRead--) {
		auto pos = pWav->readCursorInPCMFrames;
		if (pos >= pWav->totalPCMFrameCount)
			break;

		if (pWav->channels == 1) {
			*pBufferOut++ = fil_select == 2 ? wavfil2[pos] : wavfil[pos];

		} else if (pWav->channels == 2) {
			*pBufferOut++ = fil_select == 2 ? wavfil2[pos * 2] : wavfil[pos * 2];
			*pBufferOut++ = fil_select == 2 ? wavfil2[pos * 2 + 1] : wavfil[pos * 2 + 1];
		}

		numRead++;

		pWav->readCursorInPCMFrames++;
	}

	return numRead;
}

drwav_uint64 drwav_read_pcm_frames_s16(drwav *pWav, drwav_uint64 framesToRead, drwav_int16 *pBufferOut) {

	drwav_uint64 numRead = 0;

	while (framesToRead--) {
		auto pos = pWav->readCursorInPCMFrames;
		if (pos >= pWav->totalPCMFrameCount)
			break;

		if (pWav->channels == 1) {
			*pBufferOut++ = fil_select == 2 ? wavfil2_s16[pos] : wavfil_s16[pos];

		} else if (pWav->channels == 2) {
			*pBufferOut++ = fil_select == 2 ? wavfil2_s16[pos * 2] : wavfil_s16[pos * 2];
			*pBufferOut++ = fil_select == 2 ? wavfil2_s16[pos * 2 + 1] : wavfil_s16[pos * 2 + 1];
		}

		numRead++;

		pWav->readCursorInPCMFrames++;
	}

	return numRead;
}

drwav_bool32 drwav_seek_to_pcm_frame(drwav *pWav, drwav_uint64 frame_num) {
	pWav->readCursorInPCMFrames = frame_num;
	return 1;
}

TEST_CASE("Test our mocks") {

	drwav wav;
	drwav_init_file(&wav, "", nullptr);

	std::array<float, 16> out{};
	auto num = drwav_read_pcm_frames_f32(&wav, 2, out.data());

	CHECK(num == 2);
	CHECK(out[0] == 1);
	CHECK(out[1] == 2);
	CHECK(out[2] == 3);
	CHECK(out[3] == 4);
	CHECK(out[4] == 0);

	num = drwav_read_pcm_frames_f32(&wav, 2, out.data() + 4);
	CHECK(num == 2);
	CHECK(out[4] == 5);
	CHECK(out[5] == 6);
	CHECK(out[6] == 7);
	CHECK(out[7] == 8);

	num = drwav_read_pcm_frames_f32(&wav, 5, out.data() + 8);
	CHECK(num == 4);
	CHECK(out[8] == 9);
	CHECK(out[9] == 10);
	CHECK(out[10] == 11);
	CHECK(out[11] == 12);
	CHECK(out[12] == 13);
	CHECK(out[13] == 14);
	CHECK(out[14] == 15);
	CHECK(out[15] == 16);

	num = drwav_read_pcm_frames_f32(&wav, 1, out.data());
	CHECK(num == 0);
}

auto sampleval = [](float x) {
	//convert s16 to float
	return doctest::Approx(x / INT16_MAX);
};

TEST_CASE("Looping when wavfil fits in buffer") {
	fil_select = 1;
	MetaModule::WavFileStream stream{256};
	stream.load("");
	// CHECK(stream.pre_buff.get_read_pos() == 0);
	// CHECK(stream.pre_buff.get_write_pos() == 0);
	CHECK(stream.current_playback_frame() == 0);
	CHECK(stream.frames_available() == 0);
	CHECK(stream.total_frames() == 8);

	stream.read_frames_from_file(4);
	CHECK(stream.frames_available() == 4);

	CHECK(stream.current_playback_frame() == 0);
	CHECK(stream.pop_sample() == doctest::Approx(1.f / INT16_MAX));
	CHECK(stream.pop_sample() == doctest::Approx(2.f / INT16_MAX));
	CHECK(stream.frames_available() == 3);
	CHECK(stream.current_playback_frame() == 1);
	CHECK(stream.pop_sample() == sampleval(3.f));
	CHECK(stream.pop_sample() == sampleval(4.f));
	CHECK(stream.frames_available() == 2);
	CHECK(stream.current_playback_frame() == 2);
	CHECK(stream.pop_sample() == sampleval(5.f));
	CHECK(stream.pop_sample() == sampleval(6.f));
	CHECK(stream.frames_available() == 1);
	CHECK(stream.current_playback_frame() == 3);
	CHECK(stream.pop_sample() == sampleval(7.f));
	CHECK(stream.pop_sample() == sampleval(8.f));
	CHECK(stream.frames_available() == 0);
	CHECK(stream.current_playback_frame() == 4);

	// fs thread
	stream.read_frames_from_file(4);
	CHECK(stream.is_eof());

	CHECK(stream.frames_available() == 4);
	CHECK(stream.current_playback_frame() == 4);

	CHECK(stream.pop_sample() == sampleval(9.f));
	CHECK(stream.pop_sample() == sampleval(10.f));
	CHECK(stream.frames_available() == 3);
	CHECK(stream.current_playback_frame() == 5);

	CHECK(stream.pop_sample() == sampleval(11.f));
	CHECK(stream.pop_sample() == sampleval(12.f));
	CHECK(stream.frames_available() == 2);
	CHECK(stream.current_playback_frame() == 6);

	// fs thread: Loop in file (should do nothing since the file is fully buffered)
	stream.seek_frame_in_file(0);

	// audio thread:
	CHECK(stream.pop_sample() == sampleval(13.f));
	CHECK(stream.pop_sample() == sampleval(14.f));
	CHECK(stream.frames_available() == 1);
	CHECK(stream.current_playback_frame() == 7);

	CHECK(stream.pop_sample() == sampleval(15.f));
	CHECK(stream.pop_sample() == sampleval(16.f));
	CHECK(stream.frames_available() == 0);
	CHECK(stream.current_playback_frame() == 8);

	// now, current_frame >= total_frames(), so we loop in the buffer
	stream.reset_playback_to_frame(0);

	CHECK(stream.current_playback_frame() == 0);
	CHECK(stream.frames_available() == 8);
	CHECK(stream.pop_sample() == sampleval(1.f));
	CHECK(stream.pop_sample() == sampleval(2.f));

	CHECK(stream.frames_available() == 7);
	CHECK(stream.current_playback_frame() == 1);
}

TEST_CASE("Looping when wavfile is larger than buffer") {
	fil_select = 2;
	MetaModule::WavFileStream stream{8}; // 8 samples = 4 frames. Wavfil2 is 10 samples, 5 frames
	stream.load("");

	CHECK(stream.current_playback_frame() == 0);
	CHECK(stream.frames_available() == 0);
	CHECK(stream.total_frames() == 5);

	// FS thread reads min block (4)
	stream.read_frames_from_file(4);
	CHECK(stream.frames_available() == 4);

	// Audio thread pops 4 frames
	CHECK(stream.current_playback_frame() == 0);
	CHECK(stream.pop_sample() == sampleval(100.f));
	CHECK(stream.pop_sample() == sampleval(2.f));
	CHECK(stream.frames_available() == 3);
	CHECK(stream.current_playback_frame() == 1);

	CHECK(stream.pop_sample() == sampleval(3.f));
	CHECK(stream.pop_sample() == sampleval(4.f));
	CHECK(stream.frames_available() == 2);
	CHECK(stream.current_playback_frame() == 2);

	CHECK(stream.pop_sample() == sampleval(5.f));
	CHECK(stream.pop_sample() == sampleval(6.f));
	CHECK(stream.frames_available() == 1);
	CHECK(stream.current_playback_frame() == 3);

	CHECK(stream.pop_sample() == sampleval(7.f));
	CHECK(stream.pop_sample() == sampleval(8.f));
	CHECK(stream.frames_available() == 0);
	CHECK(stream.current_playback_frame() == 4);

	// FS thread reads min block, hits eof
	stream.read_frames_from_file(4);
	CHECK(stream.is_eof());

	// Audio thread status (has 1 frame available)
	CHECK(stream.frames_available() == 1);
	CHECK(stream.current_playback_frame() == 4);

	// FS thread seeks back to 0 -> clears eof
	stream.seek_frame_in_file(0);
	CHECK(!stream.is_eof());

	// No new frames are availble, nor has playback pos changed
	CHECK(stream.frames_available() == 1);
	CHECK(stream.current_playback_frame() == 4);

	SUBCASE("Audio gets ahead of FS") {
		// Audio thread pops the last frame
		CHECK(stream.pop_sample() == sampleval(9.f));
		CHECK(stream.pop_sample() == sampleval(10.f));
		CHECK(stream.frames_available() == 0);
		CHECK(stream.current_playback_frame() == 5);

		// Loop because current_playback_frame == total_frames
		// Should do nothing
		stream.reset_playback_to_frame(0);

		CHECK(stream.current_playback_frame() == 0);
		CHECK(stream.frames_available() == 0);

		// FS reads 4 more frames:
		stream.read_frames_from_file(4);
		CHECK(!stream.is_eof());
		// now these 4 frames are available
		CHECK(stream.frames_available() == 4);
		// playback pos didn't change
		CHECK(stream.current_playback_frame() == 0);
	}

	SUBCASE("FS stays ahead of Audio") {
		CHECK(stream.current_playback_frame() == 4);
		CHECK(stream.frames_available() == 1);

		// FS reads 2 frames (avoids overflow)
		stream.read_frames_from_file(2);

		// play pos doesn't change
		CHECK(stream.current_playback_frame() == 4);
		// new frames are available.
		CHECK(stream.frames_available() == 3);

		CHECK(stream.pop_sample() == sampleval(9.f));
		CHECK(stream.pop_sample() == sampleval(10.f));
		CHECK(stream.frames_available() == 2);
		CHECK(stream.current_playback_frame() == 5);

		// Loop because current_playback_frame == total_frames
		stream.reset_playback_to_frame(0);
		CHECK(stream.current_playback_frame() == 0);
		CHECK(stream.frames_available() == 2);

		// FS reads 2 frames
		stream.read_frames_from_file(2);

		CHECK(stream.current_playback_frame() == 0);
		CHECK(stream.frames_available() == 4);
	}

	CHECK(stream.pop_sample() == sampleval(100.f));
	CHECK(stream.pop_sample() == sampleval(2.f));

	CHECK(stream.frames_available() == 3);
	CHECK(stream.current_playback_frame() == 1);
}

TEST_CASE("Looping and stopping/restarting when wavfile is larger than buffer") {
	fil_select = 2;
	MetaModule::WavFileStream stream{8}; // 8 samples = 4 frames. Wavfil2 is 10 samples, 5 frames
	stream.load("");

	CHECK(stream.current_playback_frame() == 0);
	CHECK(stream.frames_available() == 0);
	CHECK(stream.total_frames() == 5);

	// FS thread reads min block
	stream.read_frames_from_file(2);
	//    W
	// |01--|
	//  R

	stream.pop_sample();
	stream.pop_sample();
	CHECK(stream.frames_available() == 1);
	//    W
	// |01--|
	//   R

	stream.read_frames_from_file(2);
	CHECK(stream.frames_available() == 3);
	//       W
	// |0123|----|
	//   R

	stream.pop_sample();
	stream.pop_sample();
	stream.pop_sample();
	stream.pop_sample();
	CHECK(stream.frames_available() == 1);
	//       W
	// |0123|----|
	//     R

	stream.read_frames_from_file(1);
	CHECK(stream.frames_available() == 2);
	//        W
	// |-123|4---|
	//     R

	// We hit EOF, so seek back to the start
	CHECK(stream.is_eof());
	stream.seek_frame_in_file(0);
	CHECK(!stream.is_eof());

	stream.read_frames_from_file(1);
	CHECK(stream.frames_available() == 3);
	//         W
	// |--23|40--|
	//     R

	// Stopping and re-starting when frame 0 is in the buffer:

	// Audio thread gets the stop signal:
	// These pass, but use private vars:
	// CHECK(stream.next_sample_to_read.load() == 6); //sample 6 = frame 3
	// CHECK(stream.next_frame_to_write.load() == 1);
	// CHECK(stream.frames_in_buffer.load() == 4);
	// CHECK(stream.first_frame_in_buffer() == 2);

	// about to write frame 1 (sample 2)
	// we want to set tail_ to point to start of frame 0 (sample 0)
	// so we should set an offset of 2
	stream.reset_playback_to_frame(0);
	//         W
	// |--23|40--|
	//        R
	// These pass, but use private vars:
	// CHECK(stream.next_frame_to_write.load() == 1);
	// CHECK(stream.next_sample_to_read.load() == 0);
	CHECK(stream.frames_available() == 1);

	// Later, audio thread get the re-start signal
	// Resets the file pointer to 0, and next_frame_to_write to 0
	stream.seek_frame_in_file(0);
	//         W
	// |--23|40--|
	//        R
	// no change
	// These pass, but use private vars:
	// CHECK(stream.next_frame_to_write.load() == 1);
	// CHECK(stream.next_sample_to_read.load() == 0);
	CHECK(stream.frames_available() == 1);

	stream.read_frames_from_file(1);
	//          W
	// |---3|401-|
	//        R
	CHECK(stream.frames_available() == 2);
	// These pass, but use private vars:
	// CHECK(stream.next_frame_to_write.load() == 2);

	CHECK(stream.pop_sample() == sampleval(100.f));
	CHECK(stream.pop_sample() == sampleval(2.f));
	//          W
	// |---3|401-|
	//         R
	CHECK(stream.pop_sample() == sampleval(3.f));
	CHECK(stream.pop_sample() == sampleval(4.f));
	//          W
	// |---3|401-|
	//          R

	stream.read_frames_from_file(1);
	//            W
	// |----|4012|----|
	//          R
	CHECK(stream.frames_available() == 1);
	// CHECK(stream.next_frame_to_write.load() == 3);

	stream.read_frames_from_file(2);
	//              W
	// |----|--12|34--|
	//          R
	CHECK(stream.frames_available() == 3);
	// These pass, but use private vars:
	// CHECK(stream.next_frame_to_write.load() == 5);
	// CHECK(stream.next_sample_to_read.load() == 4);
	// CHECK(stream.frames_in_buffer.load() == 4);
	// CHECK(stream.first_frame_in_buffer() == 1);

	/////////////////////////////////////////////////
	// Stop and restart test for when frame 0 is not in buffer
	stream.reset_playback_to_frame(0);
	//              W
	// |----|--12|34--|
	//              R
	stream.seek_frame_in_file(0);
	//              W
	// |----|--12|34--|
	//              R
	CHECK(stream.current_playback_frame() == 0); //2???

	// Next frame read is the first frame's values (100,2)
	stream.read_frames_from_file(1);
	CHECK(stream.pop_sample() == sampleval(100.f));
	CHECK(stream.pop_sample() == sampleval(2.f));
}

TEST_CASE("Looping and stopping/restarting when wavfile is smaller than buffer") {
	fil_select = 2;
	MetaModule::WavFileStream stream{256};
	stream.load("");

	CHECK(stream.current_playback_frame() == 0);
	CHECK(stream.frames_available() == 0);
	CHECK(stream.total_frames() == 5);

	// FS thread reads whole sample
	stream.read_frames_from_file(5);
	//       W
	// |01234-------
	//  R
	CHECK(stream.frames_available() == 5);

	stream.pop_sample();
	stream.pop_sample();
	stream.pop_sample();
	stream.pop_sample();
	CHECK(stream.frames_available() == 3);
	//       W
	// |01234-------
	//    R
	CHECK(stream.current_playback_frame() == 2);

	// Audio thread gets the stop signal
	stream.reset_playback_to_frame(0);
	//       W
	// |01234-------
	//  R
	CHECK(stream.frames_available() == 5);
	CHECK(stream.current_playback_frame() == 0);

	// Later, audio thread get the re-start signal
	// Resets the file pointer to 0, and next_frame_to_write to 0
	stream.seek_frame_in_file(0);
	// 0 is in buffer, so no change:
	//       W
	// |01234-------
	//  R
	CHECK(stream.current_playback_frame() == 0);

	CHECK(stream.frames_available() == 5);
	CHECK(stream.pop_sample() == sampleval(100.f));
	CHECK(stream.pop_sample() == sampleval(2.f));
}
