
a.out:     file format elf32-littlearm


Disassembly of section .init:

00008000 <_init>:
    8000:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
    8002:	bf00      	nop
    8004:	bcf8      	pop	{r3, r4, r5, r6, r7}
    8006:	bc08      	pop	{r3}
    8008:	469e      	mov	lr, r3
    800a:	4770      	bx	lr

Disassembly of section .text:

0000800c <exit>:
    800c:	b508      	push	{r3, lr}
    800e:	2100      	movs	r1, #0
    8010:	4604      	mov	r4, r0
    8012:	f000 f9c5 	bl	83a0 <__call_exitprocs>
    8016:	f248 53b0 	movw	r3, #34224	; 0x85b0
    801a:	f2c0 0300 	movt	r3, #0
    801e:	6818      	ldr	r0, [r3, #0]
    8020:	6bc3      	ldr	r3, [r0, #60]	; 0x3c
    8022:	b103      	cbz	r3, 8026 <exit+0x1a>
    8024:	4798      	blx	r3
    8026:	4620      	mov	r0, r4
    8028:	f000 e902 	blx	8230 <_exit>

0000802c <main>:
#include "iirneon.hh"

void main()
{
	ParallelBPIIR iir;
	float out = iir.calc_4iir(1.2f);
    802c:	ed9f0a28 	vldr	s0, [pc, #160]	; 80d4 <main+0xa8>
	{
		fRec0567_0 = vdupq_n_f32(0.f);
		fRec0567_1 = vdupq_n_f32(0.f);
		fRec0567_2 = vdupq_n_f32(0.f);

		float initSlow[4] = {0.1f, 0.2f, 0.3f, 0.4f}; // default values
    8030:	e3083580 	movw	r3, #34176	; 0x8580
    8034:	e3403000 	movt	r3, #0
{
    8038:	e92d4070 	push	{r4, r5, r6, lr}
    803c:	e24dd098 	sub	sp, sp, #152	; 0x98

__extension__ extern __inline float32x4_t
__attribute__  ((__always_inline__, __gnu_inline__, __artificial__))
vdupq_n_f32 (float32_t __a)
{
  return (float32x4_t)__builtin_neon_vdup_nv4sf ((__builtin_neon_sf) __a);
    8040:	f2c00050 	vmov.i32	q8, #0	; 0x00000000
		fSlow19202122 = vld1q_f32(initSlow);

		float initConst[4] = {fConst6, fConst9, fConst12, fConst15};
    8044:	e2836010 	add	r6, r3, #16
		fConst691215 = vld1q_f32(initConst);

		float initOutmixWeights[4] = {1.f, 0.25f, 0.111111112f, 0.0625f};
    8048:	e2835020 	add	r5, r3, #32
    804c:	e28d403f 	add	r4, sp, #63	; 0x3f
		float initSlow[4] = {0.1f, 0.2f, 0.3f, 0.4f}; // default values
    8050:	e1a0c00d 	mov	ip, sp
    8054:	e893000f 	ldm	r3, {r0, r1, r2, r3}
    8058:	e3c4400f 	bic	r4, r4, #15
		float initConst[4] = {fConst6, fConst9, fConst12, fConst15};
    805c:	e28de010 	add	lr, sp, #16
		float initSlow[4] = {0.1f, 0.2f, 0.3f, 0.4f}; // default values
    8060:	e88c000f 	stm	ip, {r0, r1, r2, r3}
		fRec0567_0 = vdupq_n_f32(0.f);
    8064:	edc40b04 	vstr	d16, [r4, #16]
    8068:	edc41b06 	vstr	d17, [r4, #24]
		fRec0567_1 = vdupq_n_f32(0.f);
    806c:	edc40b08 	vstr	d16, [r4, #32]
    8070:	edc41b0a 	vstr	d17, [r4, #40]	; 0x28
		fRec0567_2 = vdupq_n_f32(0.f);
    8074:	edc40b0c 	vstr	d16, [r4, #48]	; 0x30
    8078:	edc41b0e 	vstr	d17, [r4, #56]	; 0x38

__extension__ extern __inline float32x4_t
__attribute__  ((__always_inline__, __gnu_inline__, __artificial__))
vld1q_f32 (const float32_t * __a)
{
  return (float32x4_t)__builtin_neon_vld1v4sf ((const __builtin_neon_sf *) __a);
    807c:	f46c0a9f 	vld1.32	{d16-d17}, [ip :64]
		float initConst[4] = {fConst6, fConst9, fConst12, fConst15};
    8080:	e896000f 	ldm	r6, {r0, r1, r2, r3}
		fSlow19202122 = vld1q_f32(initSlow);
    8084:	f4440aef 	vst1.64	{d16-d17}, [r4 :128]
		float initConst[4] = {fConst6, fConst9, fConst12, fConst15};
    8088:	e88e000f 	stm	lr, {r0, r1, r2, r3}
		float initOutmixWeights[4] = {1.f, 0.25f, 0.111111112f, 0.0625f};
    808c:	e28dc020 	add	ip, sp, #32
    8090:	f46e0a9f 	vld1.32	{d16-d17}, [lr :64]
    8094:	e895000f 	ldm	r5, {r0, r1, r2, r3}
		fConst691215 = vld1q_f32(initConst);
    8098:	edc40b10 	vstr	d16, [r4, #64]	; 0x40
    809c:	edc41b12 	vstr	d17, [r4, #72]	; 0x48
		float initOutmixWeights[4] = {1.f, 0.25f, 0.111111112f, 0.0625f};
    80a0:	e88c000f 	stm	ip, {r0, r1, r2, r3}
	float out = iir.calc_4iir(1.2f);
    80a4:	e1a00004 	mov	r0, r4
    80a8:	f46c0a9f 	vld1.32	{d16-d17}, [ip :64]
		outmixWeights = vld1q_f32(initOutmixWeights);
    80ac:	edc40b14 	vstr	d16, [r4, #80]	; 0x50
    80b0:	edc41b16 	vstr	d17, [r4, #88]	; 0x58
    80b4:	eb00005e 	bl	8234 <_ZN13ParallelBPIIR9calc_4iirEf>
	out = iir.calc_4iir(1.3f);
    80b8:	ed9f0a06 	vldr	s0, [pc, #24]	; 80d8 <main+0xac>
    80bc:	e1a00004 	mov	r0, r4
    80c0:	eb00005b 	bl	8234 <_ZN13ParallelBPIIR9calc_4iirEf>
	volatile int x = out;
    80c4:	eebd0ac0 	vcvt.s32.f32	s0, s0
    80c8:	ed8d0a08 	vstr	s0, [sp, #32]
}
    80cc:	e28dd098 	add	sp, sp, #152	; 0x98
    80d0:	e8bd8070 	pop	{r4, r5, r6, pc}
    80d4:	3f99999a 	.word	0x3f99999a
    80d8:	3fa66666 	.word	0x3fa66666

000080dc <register_fini>:
    80dc:	f240 0300 	movw	r3, #0
    80e0:	f2c0 0300 	movt	r3, #0
    80e4:	b12b      	cbz	r3, 80f2 <register_fini+0x16>
    80e6:	f248 4071 	movw	r0, #33905	; 0x8471
    80ea:	f2c0 0000 	movt	r0, #0
    80ee:	f000 b9b9 	b.w	8464 <atexit>
    80f2:	4770      	bx	lr

000080f4 <__do_global_dtors_aux>:
    80f4:	b510      	push	{r4, lr}
    80f6:	f648 2424 	movw	r4, #35364	; 0x8a24
    80fa:	f2c0 0401 	movt	r4, #1
    80fe:	7823      	ldrb	r3, [r4, #0]
    8100:	b963      	cbnz	r3, 811c <__do_global_dtors_aux+0x28>
    8102:	f240 0300 	movw	r3, #0
    8106:	f2c0 0300 	movt	r3, #0
    810a:	b12b      	cbz	r3, 8118 <__do_global_dtors_aux+0x24>
    810c:	f248 50e0 	movw	r0, #34272	; 0x85e0
    8110:	f2c0 0000 	movt	r0, #0
    8114:	f3af 8000 	nop.w
    8118:	2301      	movs	r3, #1
    811a:	7023      	strb	r3, [r4, #0]
    811c:	bd10      	pop	{r4, pc}
    811e:	bf00      	nop

00008120 <frame_dummy>:
    8120:	b508      	push	{r3, lr}
    8122:	f240 0300 	movw	r3, #0
    8126:	f2c0 0300 	movt	r3, #0
    812a:	b14b      	cbz	r3, 8140 <frame_dummy+0x20>
    812c:	f648 2128 	movw	r1, #35368	; 0x8a28
    8130:	f2c0 0101 	movt	r1, #1
    8134:	f248 50e0 	movw	r0, #34272	; 0x85e0
    8138:	f2c0 0000 	movt	r0, #0
    813c:	f3af 8000 	nop.w
    8140:	bd08      	pop	{r3, pc}
    8142:	bf00      	nop

00008144 <_stack_init>:
    8144:	f3ef 8400 	mrs	r4, CPSR
    8148:	f014 0f0f 	tst.w	r4, #15
    814c:	d031      	beq.n	81b2 <_stack_init+0x6e>
    814e:	466b      	mov	r3, sp
    8150:	f04f 01d1 	mov.w	r1, #209	; 0xd1
    8154:	f381 8100 	msr	CPSR_c, r1
    8158:	469d      	mov	sp, r3
    815a:	f5ad 5a80 	sub.w	sl, sp, #4096	; 0x1000
    815e:	4653      	mov	r3, sl
    8160:	f04f 01d7 	mov.w	r1, #215	; 0xd7
    8164:	f381 8100 	msr	CPSR_c, r1
    8168:	469d      	mov	sp, r3
    816a:	f5a3 5380 	sub.w	r3, r3, #4096	; 0x1000
    816e:	f04f 01db 	mov.w	r1, #219	; 0xdb
    8172:	f381 8100 	msr	CPSR_c, r1
    8176:	469d      	mov	sp, r3
    8178:	f5a3 5380 	sub.w	r3, r3, #4096	; 0x1000
    817c:	f04f 01d2 	mov.w	r1, #210	; 0xd2
    8180:	f381 8100 	msr	CPSR_c, r1
    8184:	469d      	mov	sp, r3
    8186:	f5a3 5300 	sub.w	r3, r3, #8192	; 0x2000
    818a:	f04f 01d3 	mov.w	r1, #211	; 0xd3
    818e:	f381 8100 	msr	CPSR_c, r1
    8192:	469d      	mov	sp, r3
    8194:	f5a3 4300 	sub.w	r3, r3, #32768	; 0x8000
    8198:	f023 03ff 	bic.w	r3, r3, #255	; 0xff
    819c:	f423 437f 	bic.w	r3, r3, #65280	; 0xff00
    81a0:	f04f 01df 	mov.w	r1, #223	; 0xdf
    81a4:	f381 8100 	msr	CPSR_c, r1
    81a8:	469d      	mov	sp, r3
    81aa:	f044 04c0 	orr.w	r4, r4, #192	; 0xc0
    81ae:	f384 8100 	msr	CPSR_c, r4
    81b2:	f5a3 3a80 	sub.w	sl, r3, #65536	; 0x10000
    81b6:	4770      	bx	lr

000081b8 <_mainCRTStartup>:
    81b8:	4b17      	ldr	r3, [pc, #92]	; (8218 <_mainCRTStartup+0x60>)
    81ba:	2b00      	cmp	r3, #0
    81bc:	bf08      	it	eq
    81be:	4b13      	ldreq	r3, [pc, #76]	; (820c <_mainCRTStartup+0x54>)
    81c0:	469d      	mov	sp, r3
    81c2:	f7ff ffbf 	bl	8144 <_stack_init>
    81c6:	2100      	movs	r1, #0
    81c8:	468b      	mov	fp, r1
    81ca:	460f      	mov	r7, r1
    81cc:	4813      	ldr	r0, [pc, #76]	; (821c <_mainCRTStartup+0x64>)
    81ce:	4a14      	ldr	r2, [pc, #80]	; (8220 <_mainCRTStartup+0x68>)
    81d0:	1a12      	subs	r2, r2, r0
    81d2:	f000 f893 	bl	82fc <memset>
    81d6:	4b0e      	ldr	r3, [pc, #56]	; (8210 <_mainCRTStartup+0x58>)
    81d8:	2b00      	cmp	r3, #0
    81da:	d000      	beq.n	81de <_mainCRTStartup+0x26>
    81dc:	4798      	blx	r3
    81de:	4b0d      	ldr	r3, [pc, #52]	; (8214 <_mainCRTStartup+0x5c>)
    81e0:	2b00      	cmp	r3, #0
    81e2:	d000      	beq.n	81e6 <_mainCRTStartup+0x2e>
    81e4:	4798      	blx	r3
    81e6:	2000      	movs	r0, #0
    81e8:	2100      	movs	r1, #0
    81ea:	0004      	movs	r4, r0
    81ec:	000d      	movs	r5, r1
    81ee:	480d      	ldr	r0, [pc, #52]	; (8224 <_mainCRTStartup+0x6c>)
    81f0:	2800      	cmp	r0, #0
    81f2:	d002      	beq.n	81fa <_mainCRTStartup+0x42>
    81f4:	480c      	ldr	r0, [pc, #48]	; (8228 <_mainCRTStartup+0x70>)
    81f6:	f000 f935 	bl	8464 <atexit>
    81fa:	f000 f857 	bl	82ac <__libc_init_array>
    81fe:	0020      	movs	r0, r4
    8200:	0029      	movs	r1, r5
    8202:	f7ff ef14 	blx	802c <main>
    8206:	f7ff ff01 	bl	800c <exit>
    820a:	bf00      	nop
    820c:	00080000 	.word	0x00080000
	...
    821c:	00018a24 	.word	0x00018a24
    8220:	00018a64 	.word	0x00018a64
    8224:	00008465 	.word	0x00008465
    8228:	00008471 	.word	0x00008471

0000822c <__exit>:

		return vget_lane_f32(sum_tmp1, 0) + vget_lane_f32(sum_tmp1, 1);
	}
};

extern "C" void __exit() {}
    822c:	e12fff1e 	bx	lr

00008230 <_exit>:

extern "C" void _exit(int) {}
    8230:	e12fff1e 	bx	lr

00008234 <_ZN13ParallelBPIIR9calc_4iirEf>:
  return (float32x4_t) __builtin_neon_vmulfv4sf (__a, __b);
    8234:	edd08b08 	vldr	d24, [r0, #32] //q12 = r0 + #32,36,40,44 : fRec_1
    8238:	edd09b0a 	vldr	d25, [r0, #40]	; 0x28
    823c:	f4604aef 	vld1.64	{d20-d21}, [r0 :128] //q10 = r0 + #128,132,136,140 : fSlow
  return (float32x4_t)__builtin_neon_vmlav4sf (__a, __b, __c);
    8240:	edd00b0c 	vldr	d16, [r0, #48]	; 0x30 //q8 = r0 + 48,52,56,60 (fRec_2)
    8244:	edd01b0e 	vldr	d17, [r0, #56]	; 0x38
    8248:	edd06b10 	vldr	d22, [r0, #64]	; 0x40 //q11 = r0 + 64,68,72,76 (fconst)
    824c:	edd07b12 	vldr	d23, [r0, #72]	; 0x48
  return (float32x4_t) __builtin_neon_vmulfv4sf (__a, __b);
    8250:	f3444df8 	vmul.f32	q10, q10, q12  //q10 => tmp0 = fSlow (q10) * fRec_1 (q12)
  return (float32x4_t)__builtin_neon_vdup_nv4sf ((__builtin_neon_sf) __a);
    8254:	f3b40c40 	vdup.32	q0, d0[0]  //s0 = in, so q0 = in,in,in,in
  return (float32x4_t)__builtin_neon_vmlav4sf (__a, __b, __c);
    8258:	f2464df0 	vmla.f32	q10, q11, q8 //tmp0 += fConst (q11) * fRec_2 (q8)
  return (float32x4_t) __builtin_neon_vmulfv4sf (__a, __b);
    825c:	edd02b14 	vldr	d18, [r0, #80]	; 0x50  //q9 = r0 + 80,84,88,92 : (outMixWeights)
    8260:	edd03b16 	vldr	d19, [r0, #88]	; 0x58
  return (float32x4_t)__builtin_neon_vmaxfv4sf (__a, __b);
    8264:	f2488fe8 	vmax.f32	q12, q12, q12 //nop: q12 is already fRec1
		fRec0567_2 = vmaxq_f32(fRec0567_1, fRec0567_1);
    8268:	edc08b0c 	vstr	d24, [r0, #48]	; 0x30 //store fRec1 (q12) into fRec2's position
    826c:	edc09b0e 	vstr	d25, [r0, #56]	; 0x38
  return (float32x4_t) __builtin_neon_vsubv4sf (__a, __b);
    8270:	f2200d64 	vsub.f32	q0, q0, q10 //fRec0 (q0) = in (q0) - tmp0 (q10)
    8274:	f2600d60 	vsub.f32	q8, q0, q8 //diff_02 (q8) = frec0(q0) - frec2)(q8)
  return (float32x4_t)__builtin_neon_vmaxfv4sf (__a, __b);
    8278:	f2404f40 	vmax.f32	q10, q0, q0 //frec1 => q10 = frec0(q0)
  return (float32x4_t) __builtin_neon_vmulfv4sf (__a, __b);
    827c:	f3400df2 	vmul.f32	q8, q8, q9 //outvec(q8) = diff_02(q8) * outmixWeights(q9)
		fRec0567_0 = vsubq_f32(in_v, tmp0);
    8280:	ed800b04 	vstr	d0, [r0, #16] //store q0 (freq0) into ? must be frec0's pos
    8284:	ed801b06 	vstr	d1, [r0, #24]
  return (float32x2_t)__builtin_neon_vpaddv2sf (__a, __b);
    8288:	f3400da1 	vpadd.f32	d16, d16, d17  //d16 = s32 + s33 | s34 + s35
		fRec0567_1 = vmaxq_f32(fRec0567_0, fRec0567_0);
    828c:	edc04b08 	vstr	d20, [r0, #32] //store q10 (frec1 which now = frec0) into frec1's pos
    8290:	edc05b0a 	vstr	d21, [r0, #40]	; 0x28
  return (float32_t)__builtin_neon_vget_lanev2sf (__a, __b);
    8294:	ee103b90 	vmov.32	r3, d16[0] //sum d16's two lanes
    8298:	ee073a90 	vmov	s15, r3
    829c:	ee303b90 	vmov.32	r3, d16[1]
    82a0:	ee003a10 	vmov	s0, r3
	}
    82a4:	ee300a27 	vadd.f32	s0, s0, s15
    82a8:	e12fff1e 	bx	lr

000082ac <__libc_init_array>:
    82ac:	b570      	push	{r4, r5, r6, lr}
    82ae:	f248 56e4 	movw	r6, #34276	; 0x85e4
    82b2:	f2c0 0601 	movt	r6, #1
    82b6:	f248 55e4 	movw	r5, #34276	; 0x85e4
    82ba:	f2c0 0501 	movt	r5, #1
    82be:	1b76      	subs	r6, r6, r5
    82c0:	10b6      	asrs	r6, r6, #2
    82c2:	d006      	beq.n	82d2 <__libc_init_array+0x26>
    82c4:	2400      	movs	r4, #0
    82c6:	f855 3b04 	ldr.w	r3, [r5], #4
    82ca:	3401      	adds	r4, #1
    82cc:	4798      	blx	r3
    82ce:	42a6      	cmp	r6, r4
    82d0:	d1f9      	bne.n	82c6 <__libc_init_array+0x1a>
    82d2:	f248 56ec 	movw	r6, #34284	; 0x85ec
    82d6:	f2c0 0601 	movt	r6, #1
    82da:	f248 55e4 	movw	r5, #34276	; 0x85e4
    82de:	f2c0 0501 	movt	r5, #1
    82e2:	1b76      	subs	r6, r6, r5
    82e4:	f7ff fe8c 	bl	8000 <_init>
    82e8:	10b6      	asrs	r6, r6, #2
    82ea:	d006      	beq.n	82fa <__libc_init_array+0x4e>
    82ec:	2400      	movs	r4, #0
    82ee:	f855 3b04 	ldr.w	r3, [r5], #4
    82f2:	3401      	adds	r4, #1
    82f4:	4798      	blx	r3
    82f6:	42a6      	cmp	r6, r4
    82f8:	d1f9      	bne.n	82ee <__libc_init_array+0x42>
    82fa:	bd70      	pop	{r4, r5, r6, pc}

000082fc <memset>:
    82fc:	b530      	push	{r4, r5, lr}
    82fe:	0783      	lsls	r3, r0, #30
    8300:	d048      	beq.n	8394 <memset+0x98>
    8302:	1e54      	subs	r4, r2, #1
    8304:	2a00      	cmp	r2, #0
    8306:	d03f      	beq.n	8388 <memset+0x8c>
    8308:	b2ca      	uxtb	r2, r1
    830a:	4603      	mov	r3, r0
    830c:	e001      	b.n	8312 <memset+0x16>
    830e:	3c01      	subs	r4, #1
    8310:	d33a      	bcc.n	8388 <memset+0x8c>
    8312:	f803 2b01 	strb.w	r2, [r3], #1
    8316:	079d      	lsls	r5, r3, #30
    8318:	d1f9      	bne.n	830e <memset+0x12>
    831a:	2c03      	cmp	r4, #3
    831c:	d92d      	bls.n	837a <memset+0x7e>
    831e:	b2cd      	uxtb	r5, r1
    8320:	2c0f      	cmp	r4, #15
    8322:	ea45 2505 	orr.w	r5, r5, r5, lsl #8
    8326:	ea45 4505 	orr.w	r5, r5, r5, lsl #16
    832a:	d936      	bls.n	839a <memset+0x9e>
    832c:	f1a4 0210 	sub.w	r2, r4, #16
    8330:	f103 0e20 	add.w	lr, r3, #32
    8334:	f022 0c0f 	bic.w	ip, r2, #15
    8338:	44e6      	add	lr, ip
    833a:	ea4f 1c12 	mov.w	ip, r2, lsr #4
    833e:	f103 0210 	add.w	r2, r3, #16
    8342:	e942 5504 	strd	r5, r5, [r2, #-16]
    8346:	e942 5502 	strd	r5, r5, [r2, #-8]
    834a:	3210      	adds	r2, #16
    834c:	4572      	cmp	r2, lr
    834e:	d1f8      	bne.n	8342 <memset+0x46>
    8350:	f10c 0201 	add.w	r2, ip, #1
    8354:	f014 0f0c 	tst.w	r4, #12
    8358:	f004 0c0f 	and.w	ip, r4, #15
    835c:	eb03 1202 	add.w	r2, r3, r2, lsl #4
    8360:	d013      	beq.n	838a <memset+0x8e>
    8362:	f1ac 0304 	sub.w	r3, ip, #4
    8366:	f023 0303 	bic.w	r3, r3, #3
    836a:	3304      	adds	r3, #4
    836c:	4413      	add	r3, r2
    836e:	f842 5b04 	str.w	r5, [r2], #4
    8372:	4293      	cmp	r3, r2
    8374:	d1fb      	bne.n	836e <memset+0x72>
    8376:	f00c 0403 	and.w	r4, ip, #3
    837a:	b12c      	cbz	r4, 8388 <memset+0x8c>
    837c:	b2ca      	uxtb	r2, r1
    837e:	441c      	add	r4, r3
    8380:	f803 2b01 	strb.w	r2, [r3], #1
    8384:	429c      	cmp	r4, r3
    8386:	d1fb      	bne.n	8380 <memset+0x84>
    8388:	bd30      	pop	{r4, r5, pc}
    838a:	4613      	mov	r3, r2
    838c:	4664      	mov	r4, ip
    838e:	2c00      	cmp	r4, #0
    8390:	d1f4      	bne.n	837c <memset+0x80>
    8392:	e7f9      	b.n	8388 <memset+0x8c>
    8394:	4603      	mov	r3, r0
    8396:	4614      	mov	r4, r2
    8398:	e7bf      	b.n	831a <memset+0x1e>
    839a:	461a      	mov	r2, r3
    839c:	46a4      	mov	ip, r4
    839e:	e7e0      	b.n	8362 <memset+0x66>

000083a0 <__call_exitprocs>:
    83a0:	e92d 4ff0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
    83a4:	f648 2320 	movw	r3, #35360	; 0x8a20
    83a8:	f2c0 0301 	movt	r3, #1
    83ac:	b083      	sub	sp, #12
    83ae:	460f      	mov	r7, r1
    83b0:	e9cd 0300 	strd	r0, r3, [sp]
    83b4:	6818      	ldr	r0, [r3, #0]
    83b6:	f000 f87b 	bl	84b0 <__retarget_lock_acquire_recursive>
    83ba:	f248 53b0 	movw	r3, #34224	; 0x85b0
    83be:	f2c0 0300 	movt	r3, #0
    83c2:	f8d3 8000 	ldr.w	r8, [r3]
    83c6:	f8d8 6148 	ldr.w	r6, [r8, #328]	; 0x148
    83ca:	b196      	cbz	r6, 83f2 <__call_exitprocs+0x52>
    83cc:	f04f 0901 	mov.w	r9, #1
    83d0:	f04f 0a00 	mov.w	sl, #0
    83d4:	6874      	ldr	r4, [r6, #4]
    83d6:	1e65      	subs	r5, r4, #1
    83d8:	d40b      	bmi.n	83f2 <__call_exitprocs+0x52>
    83da:	3401      	adds	r4, #1
    83dc:	eb06 0484 	add.w	r4, r6, r4, lsl #2
    83e0:	b177      	cbz	r7, 8400 <__call_exitprocs+0x60>
    83e2:	f8d4 3100 	ldr.w	r3, [r4, #256]	; 0x100
    83e6:	42bb      	cmp	r3, r7
    83e8:	d00a      	beq.n	8400 <__call_exitprocs+0x60>
    83ea:	3d01      	subs	r5, #1
    83ec:	3c04      	subs	r4, #4
    83ee:	1c6b      	adds	r3, r5, #1
    83f0:	d1f6      	bne.n	83e0 <__call_exitprocs+0x40>
    83f2:	9b01      	ldr	r3, [sp, #4]
    83f4:	6818      	ldr	r0, [r3, #0]
    83f6:	b003      	add	sp, #12
    83f8:	e8bd 4ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
    83fc:	f000 b860 	b.w	84c0 <__retarget_lock_release_recursive>
    8400:	6822      	ldr	r2, [r4, #0]
    8402:	6873      	ldr	r3, [r6, #4]
    8404:	3b01      	subs	r3, #1
    8406:	42ab      	cmp	r3, r5
    8408:	bf0c      	ite	eq
    840a:	6075      	streq	r5, [r6, #4]
    840c:	f8c4 a000 	strne.w	sl, [r4]
    8410:	2a00      	cmp	r2, #0
    8412:	d0ea      	beq.n	83ea <__call_exitprocs+0x4a>
    8414:	f8d6 0188 	ldr.w	r0, [r6, #392]	; 0x188
    8418:	fa09 f105 	lsl.w	r1, r9, r5
    841c:	f8d6 b004 	ldr.w	fp, [r6, #4]
    8420:	4201      	tst	r1, r0
    8422:	d10b      	bne.n	843c <__call_exitprocs+0x9c>
    8424:	4790      	blx	r2
    8426:	6872      	ldr	r2, [r6, #4]
    8428:	455a      	cmp	r2, fp
    842a:	d112      	bne.n	8452 <__call_exitprocs+0xb2>
    842c:	f8d8 3148 	ldr.w	r3, [r8, #328]	; 0x148
    8430:	42b3      	cmp	r3, r6
    8432:	d0da      	beq.n	83ea <__call_exitprocs+0x4a>
    8434:	461e      	mov	r6, r3
    8436:	2e00      	cmp	r6, #0
    8438:	d1cc      	bne.n	83d4 <__call_exitprocs+0x34>
    843a:	e7da      	b.n	83f2 <__call_exitprocs+0x52>
    843c:	f8d6 018c 	ldr.w	r0, [r6, #396]	; 0x18c
    8440:	4201      	tst	r1, r0
    8442:	d10b      	bne.n	845c <__call_exitprocs+0xbc>
    8444:	f8d4 1080 	ldr.w	r1, [r4, #128]	; 0x80
    8448:	9800      	ldr	r0, [sp, #0]
    844a:	4790      	blx	r2
    844c:	6872      	ldr	r2, [r6, #4]
    844e:	455a      	cmp	r2, fp
    8450:	d0ec      	beq.n	842c <__call_exitprocs+0x8c>
    8452:	f8d8 6148 	ldr.w	r6, [r8, #328]	; 0x148
    8456:	2e00      	cmp	r6, #0
    8458:	d1bc      	bne.n	83d4 <__call_exitprocs+0x34>
    845a:	e7ca      	b.n	83f2 <__call_exitprocs+0x52>
    845c:	f8d4 0080 	ldr.w	r0, [r4, #128]	; 0x80
    8460:	4790      	blx	r2
    8462:	e7e0      	b.n	8426 <__call_exitprocs+0x86>

00008464 <atexit>:
    8464:	2300      	movs	r3, #0
    8466:	4601      	mov	r1, r0
    8468:	461a      	mov	r2, r3
    846a:	4618      	mov	r0, r3
    846c:	f000 b82a 	b.w	84c4 <__register_exitproc>

00008470 <__libc_fini_array>:
    8470:	b538      	push	{r3, r4, r5, lr}
    8472:	f248 55f0 	movw	r5, #34288	; 0x85f0
    8476:	f2c0 0501 	movt	r5, #1
    847a:	f248 54ec 	movw	r4, #34284	; 0x85ec
    847e:	f2c0 0401 	movt	r4, #1
    8482:	1b2c      	subs	r4, r5, r4
    8484:	10a4      	asrs	r4, r4, #2
    8486:	d005      	beq.n	8494 <__libc_fini_array+0x24>
    8488:	f855 3d04 	ldr.w	r3, [r5, #-4]!
    848c:	3c01      	subs	r4, #1
    848e:	4798      	blx	r3
    8490:	2c00      	cmp	r4, #0
    8492:	d1f9      	bne.n	8488 <__libc_fini_array+0x18>
    8494:	e8bd 4038 	ldmia.w	sp!, {r3, r4, r5, lr}
    8498:	f000 b85a 	b.w	8550 <_fini>

0000849c <__retarget_lock_init>:
    849c:	4770      	bx	lr
    849e:	bf00      	nop

000084a0 <__retarget_lock_init_recursive>:
    84a0:	4770      	bx	lr
    84a2:	bf00      	nop

000084a4 <__retarget_lock_close>:
    84a4:	4770      	bx	lr
    84a6:	bf00      	nop

000084a8 <__retarget_lock_close_recursive>:
    84a8:	4770      	bx	lr
    84aa:	bf00      	nop

000084ac <__retarget_lock_acquire>:
    84ac:	4770      	bx	lr
    84ae:	bf00      	nop

000084b0 <__retarget_lock_acquire_recursive>:
    84b0:	4770      	bx	lr
    84b2:	bf00      	nop

000084b4 <__retarget_lock_try_acquire>:
    84b4:	2001      	movs	r0, #1
    84b6:	4770      	bx	lr

000084b8 <__retarget_lock_try_acquire_recursive>:
    84b8:	2001      	movs	r0, #1
    84ba:	4770      	bx	lr

000084bc <__retarget_lock_release>:
    84bc:	4770      	bx	lr
    84be:	bf00      	nop

000084c0 <__retarget_lock_release_recursive>:
    84c0:	4770      	bx	lr
    84c2:	bf00      	nop

000084c4 <__register_exitproc>:
    84c4:	e92d 47f0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
    84c8:	f648 2620 	movw	r6, #35360	; 0x8a20
    84cc:	f2c0 0601 	movt	r6, #1
    84d0:	4607      	mov	r7, r0
    84d2:	4699      	mov	r9, r3
    84d4:	4688      	mov	r8, r1
    84d6:	4692      	mov	sl, r2
    84d8:	6830      	ldr	r0, [r6, #0]
    84da:	f7ff ffe9 	bl	84b0 <__retarget_lock_acquire_recursive>
    84de:	f248 50b0 	movw	r0, #34224	; 0x85b0
    84e2:	f2c0 0000 	movt	r0, #0
    84e6:	6803      	ldr	r3, [r0, #0]
    84e8:	f8d3 4148 	ldr.w	r4, [r3, #328]	; 0x148
    84ec:	b32c      	cbz	r4, 853a <__register_exitproc+0x76>
    84ee:	6865      	ldr	r5, [r4, #4]
    84f0:	2d1f      	cmp	r5, #31
    84f2:	dc27      	bgt.n	8544 <__register_exitproc+0x80>
    84f4:	b957      	cbnz	r7, 850c <__register_exitproc+0x48>
    84f6:	1c6b      	adds	r3, r5, #1
    84f8:	3502      	adds	r5, #2
    84fa:	6830      	ldr	r0, [r6, #0]
    84fc:	6063      	str	r3, [r4, #4]
    84fe:	f844 8025 	str.w	r8, [r4, r5, lsl #2]
    8502:	f7ff ffdd 	bl	84c0 <__retarget_lock_release_recursive>
    8506:	2000      	movs	r0, #0
    8508:	e8bd 87f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, pc}
    850c:	eb04 0185 	add.w	r1, r4, r5, lsl #2
    8510:	2301      	movs	r3, #1
    8512:	2f02      	cmp	r7, #2
    8514:	fa03 f305 	lsl.w	r3, r3, r5
    8518:	f8c1 a088 	str.w	sl, [r1, #136]	; 0x88
    851c:	f8d4 2188 	ldr.w	r2, [r4, #392]	; 0x188
    8520:	ea42 0203 	orr.w	r2, r2, r3
    8524:	f8c4 2188 	str.w	r2, [r4, #392]	; 0x188
    8528:	f8c1 9108 	str.w	r9, [r1, #264]	; 0x108
    852c:	bf02      	ittt	eq
    852e:	f8d4 218c 	ldreq.w	r2, [r4, #396]	; 0x18c
    8532:	4313      	orreq	r3, r2
    8534:	f8c4 318c 	streq.w	r3, [r4, #396]	; 0x18c
    8538:	e7dd      	b.n	84f6 <__register_exitproc+0x32>
    853a:	f503 74a6 	add.w	r4, r3, #332	; 0x14c
    853e:	f8c3 4148 	str.w	r4, [r3, #328]	; 0x148
    8542:	e7d4      	b.n	84ee <__register_exitproc+0x2a>
    8544:	6830      	ldr	r0, [r6, #0]
    8546:	f7ff ffbb 	bl	84c0 <__retarget_lock_release_recursive>
    854a:	f04f 30ff 	mov.w	r0, #4294967295	; 0xffffffff
    854e:	e7db      	b.n	8508 <__register_exitproc+0x44>

Disassembly of section .fini:

00008550 <_fini>:
    8550:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
    8552:	bf00      	nop
    8554:	bcf8      	pop	{r3, r4, r5, r6, r7}
    8556:	bc08      	pop	{r3}
    8558:	469e      	mov	lr, r3
    855a:	4770      	bx	lr
