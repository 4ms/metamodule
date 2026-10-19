// The assets image (assets.uimg: module faceplates, fonts, etc), embedded in the A35 image until
// MP2 can read it from flash. See mp2-stubs/fs/asset_drive/asset_fs.hh.
// ASSETS_IMAGE is set by cmake/mp2.cmake. Without it, the image is empty.
	.section .rodata.assets_image, "a"
	.balign 16
	.global assets_image
assets_image:
#ifdef ASSETS_IMAGE
	.incbin ASSETS_IMAGE
#endif
	.global assets_image_end
assets_image_end:
