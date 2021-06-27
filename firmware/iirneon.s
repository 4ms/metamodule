
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
    8012:	f000 f9bd 	bl	8390 <__call_exitprocs>
    8016:	f248 53a0 	movw	r3, #34208	; 0x85a0
    801a:	f2c0 0300 	movt	r3, #0
    801e:	6818      	ldr	r0, [r3, #0]
    8020:	6bc3      	ldr	r3, [r0, #60]	; 0x3c
    8022:	b103      	cbz	r3, 8026 <exit+0x1a>
    8024:	4798      	blx	r3
    8026:	4620      	mov	r0, r4
    8028:	f000 e8fe 	blx	8228 <_exit>

0000802c <main>:
	float mixweights[4] = {1.f, 0.25f, 0.111111112f, 0.0625f};

	ParallelBPIIR iir{params, consts, mixweights};

	// run it twice
	float out = iir.calc_4iir(1.2f);
    802c:	ed9f0a26 	vldr	s0, [pc, #152]	; 80cc <main+0xa0>
	float params[4] = {0.1f, 0.2f, 0.3f, 0.4f};
    8030:	e3083570 	movw	r3, #34160	; 0x8570
    8034:	e3403000 	movt	r3, #0
{
    8038:	e92d4070 	push	{r4, r5, r6, lr}
    803c:	e24dd090 	sub	sp, sp, #144	; 0x90

__extension__ extern __inline float32x4_t
__attribute__  ((__always_inline__, __gnu_inline__, __artificial__))
vdupq_n_f32 (float32_t __a)
{
  return (float32x4_t)__builtin_neon_vdup_nv4sf ((__builtin_neon_sf) __a);
    8040:	f2c00050 	vmov.i32	q8, #0	; 0x00000000
	float consts[4] = {fConst6, fConst9, fConst12, fConst15};
    8044:	e2836010 	add	r6, r3, #16
	float mixweights[4] = {1.f, 0.25f, 0.111111112f, 0.0625f};
    8048:	e2835020 	add	r5, r3, #32
{
    804c:	e28d4047 	add	r4, sp, #71	; 0x47
	float params[4] = {0.1f, 0.2f, 0.3f, 0.4f};
    8050:	e28dc008 	add	ip, sp, #8
    8054:	e893000f 	ldm	r3, {r0, r1, r2, r3}
{
    8058:	e3c4400f 	bic	r4, r4, #15
	float consts[4] = {fConst6, fConst9, fConst12, fConst15};
    805c:	e28de018 	add	lr, sp, #24
	float params[4] = {0.1f, 0.2f, 0.3f, 0.4f};
    8060:	e88c000f 	stm	ip, {r0, r1, r2, r3}
	// float[4]: initOutmixWeights (a0?)
	// float[4]: initSlow = control-dependant values (a1?)
	// float[4]: initConst = samplerate-dependant values (a2?)
	ParallelBPIIR(float slows[4], float consts[4], float par_weights[4])
	{
		fRec0567_1 = vdupq_n_f32(0.f);
    8064:	edc40b04 	vstr	d16, [r4, #16]
    8068:	edc41b06 	vstr	d17, [r4, #24]
		fRec0567_2 = vdupq_n_f32(0.f);
    806c:	edc40b08 	vstr	d16, [r4, #32]
    8070:	edc41b0a 	vstr	d17, [r4, #40]	; 0x28

__extension__ extern __inline float32x4_t
__attribute__  ((__always_inline__, __gnu_inline__, __artificial__))
vld1q_f32 (const float32_t * __a)
{
  return (float32x4_t)__builtin_neon_vld1v4sf ((const __builtin_neon_sf *) __a);
    8074:	f46c0a9f 	vld1.32	{d16-d17}, [ip :64]
	float consts[4] = {fConst6, fConst9, fConst12, fConst15};
    8078:	e896000f 	ldm	r6, {r0, r1, r2, r3}
		fSlow19202122 = vld1q_f32(slows);
    807c:	f4440aef 	vst1.64	{d16-d17}, [r4 :128]
    8080:	e88e000f 	stm	lr, {r0, r1, r2, r3}
	float mixweights[4] = {1.f, 0.25f, 0.111111112f, 0.0625f};
    8084:	e28dc028 	add	ip, sp, #40	; 0x28
    8088:	f46e0a9f 	vld1.32	{d16-d17}, [lr :64]
    808c:	e895000f 	ldm	r5, {r0, r1, r2, r3}
		fConst691215 = vld1q_f32(consts);
    8090:	edc40b0c 	vstr	d16, [r4, #48]	; 0x30
    8094:	edc41b0e 	vstr	d17, [r4, #56]	; 0x38
    8098:	e88c000f 	stm	ip, {r0, r1, r2, r3}
	float out = iir.calc_4iir(1.2f);
    809c:	e1a00004 	mov	r0, r4
    80a0:	f46c0a9f 	vld1.32	{d16-d17}, [ip :64]
		outmixWeights = vld1q_f32(par_weights);
    80a4:	edc40b10 	vstr	d16, [r4, #64]	; 0x40
    80a8:	edc41b12 	vstr	d17, [r4, #72]	; 0x48
    80ac:	eb00005e 	bl	822c <_ZN13ParallelBPIIR9calc_4iirEf>
	out = iir.calc_4iir(1.3f);
    80b0:	ed9f0a06 	vldr	s0, [pc, #24]	; 80d0 <main+0xa4>
    80b4:	e1a00004 	mov	r0, r4
    80b8:	eb00005b 	bl	822c <_ZN13ParallelBPIIR9calc_4iirEf>

	// force compiler to keep values:
	volatile int x = out;
    80bc:	eebd0ac0 	vcvt.s32.f32	s0, s0
    80c0:	ed8d0a01 	vstr	s0, [sp, #4]
}
    80c4:	e28dd090 	add	sp, sp, #144	; 0x90
    80c8:	e8bd8070 	pop	{r4, r5, r6, pc}
    80cc:	3f99999a 	.word	0x3f99999a
    80d0:	3fa66666 	.word	0x3fa66666

000080d4 <register_fini>:
    80d4:	f240 0300 	movw	r3, #0
    80d8:	f2c0 0300 	movt	r3, #0
    80dc:	b12b      	cbz	r3, 80ea <register_fini+0x16>
    80de:	f248 4061 	movw	r0, #33889	; 0x8461
    80e2:	f2c0 0000 	movt	r0, #0
    80e6:	f000 b9b5 	b.w	8454 <atexit>
    80ea:	4770      	bx	lr

000080ec <__do_global_dtors_aux>:
    80ec:	b510      	push	{r4, lr}
    80ee:	f648 2414 	movw	r4, #35348	; 0x8a14
    80f2:	f2c0 0401 	movt	r4, #1
    80f6:	7823      	ldrb	r3, [r4, #0]
    80f8:	b963      	cbnz	r3, 8114 <__do_global_dtors_aux+0x28>
    80fa:	f240 0300 	movw	r3, #0
    80fe:	f2c0 0300 	movt	r3, #0
    8102:	b12b      	cbz	r3, 8110 <__do_global_dtors_aux+0x24>
    8104:	f248 50d0 	movw	r0, #34256	; 0x85d0
    8108:	f2c0 0000 	movt	r0, #0
    810c:	f3af 8000 	nop.w
    8110:	2301      	movs	r3, #1
    8112:	7023      	strb	r3, [r4, #0]
    8114:	bd10      	pop	{r4, pc}
    8116:	bf00      	nop

00008118 <frame_dummy>:
    8118:	b508      	push	{r3, lr}
    811a:	f240 0300 	movw	r3, #0
    811e:	f2c0 0300 	movt	r3, #0
    8122:	b14b      	cbz	r3, 8138 <frame_dummy+0x20>
    8124:	f648 2118 	movw	r1, #35352	; 0x8a18
    8128:	f2c0 0101 	movt	r1, #1
    812c:	f248 50d0 	movw	r0, #34256	; 0x85d0
    8130:	f2c0 0000 	movt	r0, #0
    8134:	f3af 8000 	nop.w
    8138:	bd08      	pop	{r3, pc}
    813a:	bf00      	nop

0000813c <_stack_init>:
    813c:	f3ef 8400 	mrs	r4, CPSR
    8140:	f014 0f0f 	tst.w	r4, #15
    8144:	d031      	beq.n	81aa <_stack_init+0x6e>
    8146:	466b      	mov	r3, sp
    8148:	f04f 01d1 	mov.w	r1, #209	; 0xd1
    814c:	f381 8100 	msr	CPSR_c, r1
    8150:	469d      	mov	sp, r3
    8152:	f5ad 5a80 	sub.w	sl, sp, #4096	; 0x1000
    8156:	4653      	mov	r3, sl
    8158:	f04f 01d7 	mov.w	r1, #215	; 0xd7
    815c:	f381 8100 	msr	CPSR_c, r1
    8160:	469d      	mov	sp, r3
    8162:	f5a3 5380 	sub.w	r3, r3, #4096	; 0x1000
    8166:	f04f 01db 	mov.w	r1, #219	; 0xdb
    816a:	f381 8100 	msr	CPSR_c, r1
    816e:	469d      	mov	sp, r3
    8170:	f5a3 5380 	sub.w	r3, r3, #4096	; 0x1000
    8174:	f04f 01d2 	mov.w	r1, #210	; 0xd2
    8178:	f381 8100 	msr	CPSR_c, r1
    817c:	469d      	mov	sp, r3
    817e:	f5a3 5300 	sub.w	r3, r3, #8192	; 0x2000
    8182:	f04f 01d3 	mov.w	r1, #211	; 0xd3
    8186:	f381 8100 	msr	CPSR_c, r1
    818a:	469d      	mov	sp, r3
    818c:	f5a3 4300 	sub.w	r3, r3, #32768	; 0x8000
    8190:	f023 03ff 	bic.w	r3, r3, #255	; 0xff
    8194:	f423 437f 	bic.w	r3, r3, #65280	; 0xff00
    8198:	f04f 01df 	mov.w	r1, #223	; 0xdf
    819c:	f381 8100 	msr	CPSR_c, r1
    81a0:	469d      	mov	sp, r3
    81a2:	f044 04c0 	orr.w	r4, r4, #192	; 0xc0
    81a6:	f384 8100 	msr	CPSR_c, r4
    81aa:	f5a3 3a80 	sub.w	sl, r3, #65536	; 0x10000
    81ae:	4770      	bx	lr

000081b0 <_mainCRTStartup>:
    81b0:	4b17      	ldr	r3, [pc, #92]	; (8210 <_mainCRTStartup+0x60>)
    81b2:	2b00      	cmp	r3, #0
    81b4:	bf08      	it	eq
    81b6:	4b13      	ldreq	r3, [pc, #76]	; (8204 <_mainCRTStartup+0x54>)
    81b8:	469d      	mov	sp, r3
    81ba:	f7ff ffbf 	bl	813c <_stack_init>
    81be:	2100      	movs	r1, #0
    81c0:	468b      	mov	fp, r1
    81c2:	460f      	mov	r7, r1
    81c4:	4813      	ldr	r0, [pc, #76]	; (8214 <_mainCRTStartup+0x64>)
    81c6:	4a14      	ldr	r2, [pc, #80]	; (8218 <_mainCRTStartup+0x68>)
    81c8:	1a12      	subs	r2, r2, r0
    81ca:	f000 f88f 	bl	82ec <memset>
    81ce:	4b0e      	ldr	r3, [pc, #56]	; (8208 <_mainCRTStartup+0x58>)
    81d0:	2b00      	cmp	r3, #0
    81d2:	d000      	beq.n	81d6 <_mainCRTStartup+0x26>
    81d4:	4798      	blx	r3
    81d6:	4b0d      	ldr	r3, [pc, #52]	; (820c <_mainCRTStartup+0x5c>)
    81d8:	2b00      	cmp	r3, #0
    81da:	d000      	beq.n	81de <_mainCRTStartup+0x2e>
    81dc:	4798      	blx	r3
    81de:	2000      	movs	r0, #0
    81e0:	2100      	movs	r1, #0
    81e2:	0004      	movs	r4, r0
    81e4:	000d      	movs	r5, r1
    81e6:	480d      	ldr	r0, [pc, #52]	; (821c <_mainCRTStartup+0x6c>)
    81e8:	2800      	cmp	r0, #0
    81ea:	d002      	beq.n	81f2 <_mainCRTStartup+0x42>
    81ec:	480c      	ldr	r0, [pc, #48]	; (8220 <_mainCRTStartup+0x70>)
    81ee:	f000 f931 	bl	8454 <atexit>
    81f2:	f000 f853 	bl	829c <__libc_init_array>
    81f6:	0020      	movs	r0, r4
    81f8:	0029      	movs	r1, r5
    81fa:	f7ff ef18 	blx	802c <main>
    81fe:	f7ff ff05 	bl	800c <exit>
    8202:	bf00      	nop
    8204:	00080000 	.word	0x00080000
	...
    8214:	00018a14 	.word	0x00018a14
    8218:	00018a54 	.word	0x00018a54
    821c:	00008455 	.word	0x00008455
    8220:	00008461 	.word	0x00008461

00008224 <__exit>:

		return vget_lane_f32(sum_tmp1, 0) + vget_lane_f32(sum_tmp1, 1);
	}
};

extern "C" void __exit() {}
    8224:	e12fff1e 	bx	lr

00008228 <_exit>:

extern "C" void _exit(int) {}
    8228:	e12fff1e 	bx	lr

0000822c <_ZN13ParallelBPIIR9calc_4iirEf>:
  return (float32x4_t) __builtin_neon_vmulfv4sf (__a, __b);
    822c:	edd08b04 	vldr	d24, [r0, #16]
    8230:	edd09b06 	vldr	d25, [r0, #24]
    8234:	f4604aef 	vld1.64	{d20-d21}, [r0 :128]
  return (float32x4_t)__builtin_neon_vmlav4sf (__a, __b, __c);
    8238:	edd00b08 	vldr	d16, [r0, #32]
    823c:	edd01b0a 	vldr	d17, [r0, #40]	; 0x28
    8240:	edd06b0c 	vldr	d22, [r0, #48]	; 0x30
    8244:	edd07b0e 	vldr	d23, [r0, #56]	; 0x38
  return (float32x4_t) __builtin_neon_vmulfv4sf (__a, __b);
    8248:	f3444df8 	vmul.f32	q10, q10, q12
  return (float32x4_t)__builtin_neon_vdup_nv4sf ((__builtin_neon_sf) __a);
    824c:	f3b40c40 	vdup.32	q0, d0[0]
  return (float32x4_t)__builtin_neon_vmlav4sf (__a, __b, __c);
    8250:	f2464df0 	vmla.f32	q10, q11, q8
  return (float32x4_t) __builtin_neon_vmulfv4sf (__a, __b);
    8254:	edd02b10 	vldr	d18, [r0, #64]	; 0x40
    8258:	edd03b12 	vldr	d19, [r0, #72]	; 0x48
  return (float32x4_t)__builtin_neon_vmaxfv4sf (__a, __b);
    825c:	f2488fe8 	vmax.f32	q12, q12, q12
		fRec0567_2 = vmaxq_f32(fRec0567_1, fRec0567_1);
    8260:	edc08b08 	vstr	d24, [r0, #32]
    8264:	edc09b0a 	vstr	d25, [r0, #40]	; 0x28
  return (float32x4_t) __builtin_neon_vsubv4sf (__a, __b);
    8268:	f2200d64 	vsub.f32	q0, q0, q10
    826c:	f2600d60 	vsub.f32	q8, q0, q8
  return (float32x4_t)__builtin_neon_vmaxfv4sf (__a, __b);
    8270:	f2000f40 	vmax.f32	q0, q0, q0
  return (float32x4_t) __builtin_neon_vmulfv4sf (__a, __b);
    8274:	f3400df2 	vmul.f32	q8, q8, q9
		fRec0567_1 = vmaxq_f32(fRec0567_0, fRec0567_0);
    8278:	ed800b04 	vstr	d0, [r0, #16]
    827c:	ed801b06 	vstr	d1, [r0, #24]
  return (float32x2_t)__builtin_neon_vpaddv2sf (__a, __b);
    8280:	f3400da1 	vpadd.f32	d16, d16, d17
  return (float32_t)__builtin_neon_vget_lanev2sf (__a, __b);
    8284:	ee103b90 	vmov.32	r3, d16[0]
    8288:	ee073a90 	vmov	s15, r3
    828c:	ee303b90 	vmov.32	r3, d16[1]
    8290:	ee003a10 	vmov	s0, r3
	}
    8294:	ee300a27 	vadd.f32	s0, s0, s15
    8298:	e12fff1e 	bx	lr

0000829c <__libc_init_array>:
    829c:	b570      	push	{r4, r5, r6, lr}
    829e:	f248 56d4 	movw	r6, #34260	; 0x85d4
    82a2:	f2c0 0601 	movt	r6, #1
    82a6:	f248 55d4 	movw	r5, #34260	; 0x85d4
    82aa:	f2c0 0501 	movt	r5, #1
    82ae:	1b76      	subs	r6, r6, r5
    82b0:	10b6      	asrs	r6, r6, #2
    82b2:	d006      	beq.n	82c2 <__libc_init_array+0x26>
    82b4:	2400      	movs	r4, #0
    82b6:	f855 3b04 	ldr.w	r3, [r5], #4
    82ba:	3401      	adds	r4, #1
    82bc:	4798      	blx	r3
    82be:	42a6      	cmp	r6, r4
    82c0:	d1f9      	bne.n	82b6 <__libc_init_array+0x1a>
    82c2:	f248 56dc 	movw	r6, #34268	; 0x85dc
    82c6:	f2c0 0601 	movt	r6, #1
    82ca:	f248 55d4 	movw	r5, #34260	; 0x85d4
    82ce:	f2c0 0501 	movt	r5, #1
    82d2:	1b76      	subs	r6, r6, r5
    82d4:	f7ff fe94 	bl	8000 <_init>
    82d8:	10b6      	asrs	r6, r6, #2
    82da:	d006      	beq.n	82ea <__libc_init_array+0x4e>
    82dc:	2400      	movs	r4, #0
    82de:	f855 3b04 	ldr.w	r3, [r5], #4
    82e2:	3401      	adds	r4, #1
    82e4:	4798      	blx	r3
    82e6:	42a6      	cmp	r6, r4
    82e8:	d1f9      	bne.n	82de <__libc_init_array+0x42>
    82ea:	bd70      	pop	{r4, r5, r6, pc}

000082ec <memset>:
    82ec:	b530      	push	{r4, r5, lr}
    82ee:	0783      	lsls	r3, r0, #30
    82f0:	d048      	beq.n	8384 <memset+0x98>
    82f2:	1e54      	subs	r4, r2, #1
    82f4:	2a00      	cmp	r2, #0
    82f6:	d03f      	beq.n	8378 <memset+0x8c>
    82f8:	b2ca      	uxtb	r2, r1
    82fa:	4603      	mov	r3, r0
    82fc:	e001      	b.n	8302 <memset+0x16>
    82fe:	3c01      	subs	r4, #1
    8300:	d33a      	bcc.n	8378 <memset+0x8c>
    8302:	f803 2b01 	strb.w	r2, [r3], #1
    8306:	079d      	lsls	r5, r3, #30
    8308:	d1f9      	bne.n	82fe <memset+0x12>
    830a:	2c03      	cmp	r4, #3
    830c:	d92d      	bls.n	836a <memset+0x7e>
    830e:	b2cd      	uxtb	r5, r1
    8310:	2c0f      	cmp	r4, #15
    8312:	ea45 2505 	orr.w	r5, r5, r5, lsl #8
    8316:	ea45 4505 	orr.w	r5, r5, r5, lsl #16
    831a:	d936      	bls.n	838a <memset+0x9e>
    831c:	f1a4 0210 	sub.w	r2, r4, #16
    8320:	f103 0e20 	add.w	lr, r3, #32
    8324:	f022 0c0f 	bic.w	ip, r2, #15
    8328:	44e6      	add	lr, ip
    832a:	ea4f 1c12 	mov.w	ip, r2, lsr #4
    832e:	f103 0210 	add.w	r2, r3, #16
    8332:	e942 5504 	strd	r5, r5, [r2, #-16]
    8336:	e942 5502 	strd	r5, r5, [r2, #-8]
    833a:	3210      	adds	r2, #16
    833c:	4572      	cmp	r2, lr
    833e:	d1f8      	bne.n	8332 <memset+0x46>
    8340:	f10c 0201 	add.w	r2, ip, #1
    8344:	f014 0f0c 	tst.w	r4, #12
    8348:	f004 0c0f 	and.w	ip, r4, #15
    834c:	eb03 1202 	add.w	r2, r3, r2, lsl #4
    8350:	d013      	beq.n	837a <memset+0x8e>
    8352:	f1ac 0304 	sub.w	r3, ip, #4
    8356:	f023 0303 	bic.w	r3, r3, #3
    835a:	3304      	adds	r3, #4
    835c:	4413      	add	r3, r2
    835e:	f842 5b04 	str.w	r5, [r2], #4
    8362:	4293      	cmp	r3, r2
    8364:	d1fb      	bne.n	835e <memset+0x72>
    8366:	f00c 0403 	and.w	r4, ip, #3
    836a:	b12c      	cbz	r4, 8378 <memset+0x8c>
    836c:	b2ca      	uxtb	r2, r1
    836e:	441c      	add	r4, r3
    8370:	f803 2b01 	strb.w	r2, [r3], #1
    8374:	429c      	cmp	r4, r3
    8376:	d1fb      	bne.n	8370 <memset+0x84>
    8378:	bd30      	pop	{r4, r5, pc}
    837a:	4613      	mov	r3, r2
    837c:	4664      	mov	r4, ip
    837e:	2c00      	cmp	r4, #0
    8380:	d1f4      	bne.n	836c <memset+0x80>
    8382:	e7f9      	b.n	8378 <memset+0x8c>
    8384:	4603      	mov	r3, r0
    8386:	4614      	mov	r4, r2
    8388:	e7bf      	b.n	830a <memset+0x1e>
    838a:	461a      	mov	r2, r3
    838c:	46a4      	mov	ip, r4
    838e:	e7e0      	b.n	8352 <memset+0x66>

00008390 <__call_exitprocs>:
    8390:	e92d 4ff0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
    8394:	f648 2310 	movw	r3, #35344	; 0x8a10
    8398:	f2c0 0301 	movt	r3, #1
    839c:	b083      	sub	sp, #12
    839e:	460f      	mov	r7, r1
    83a0:	e9cd 0300 	strd	r0, r3, [sp]
    83a4:	6818      	ldr	r0, [r3, #0]
    83a6:	f000 f87b 	bl	84a0 <__retarget_lock_acquire_recursive>
    83aa:	f248 53a0 	movw	r3, #34208	; 0x85a0
    83ae:	f2c0 0300 	movt	r3, #0
    83b2:	f8d3 8000 	ldr.w	r8, [r3]
    83b6:	f8d8 6148 	ldr.w	r6, [r8, #328]	; 0x148
    83ba:	b196      	cbz	r6, 83e2 <__call_exitprocs+0x52>
    83bc:	f04f 0901 	mov.w	r9, #1
    83c0:	f04f 0a00 	mov.w	sl, #0
    83c4:	6874      	ldr	r4, [r6, #4]
    83c6:	1e65      	subs	r5, r4, #1
    83c8:	d40b      	bmi.n	83e2 <__call_exitprocs+0x52>
    83ca:	3401      	adds	r4, #1
    83cc:	eb06 0484 	add.w	r4, r6, r4, lsl #2
    83d0:	b177      	cbz	r7, 83f0 <__call_exitprocs+0x60>
    83d2:	f8d4 3100 	ldr.w	r3, [r4, #256]	; 0x100
    83d6:	42bb      	cmp	r3, r7
    83d8:	d00a      	beq.n	83f0 <__call_exitprocs+0x60>
    83da:	3d01      	subs	r5, #1
    83dc:	3c04      	subs	r4, #4
    83de:	1c6b      	adds	r3, r5, #1
    83e0:	d1f6      	bne.n	83d0 <__call_exitprocs+0x40>
    83e2:	9b01      	ldr	r3, [sp, #4]
    83e4:	6818      	ldr	r0, [r3, #0]
    83e6:	b003      	add	sp, #12
    83e8:	e8bd 4ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
    83ec:	f000 b860 	b.w	84b0 <__retarget_lock_release_recursive>
    83f0:	6822      	ldr	r2, [r4, #0]
    83f2:	6873      	ldr	r3, [r6, #4]
    83f4:	3b01      	subs	r3, #1
    83f6:	42ab      	cmp	r3, r5
    83f8:	bf0c      	ite	eq
    83fa:	6075      	streq	r5, [r6, #4]
    83fc:	f8c4 a000 	strne.w	sl, [r4]
    8400:	2a00      	cmp	r2, #0
    8402:	d0ea      	beq.n	83da <__call_exitprocs+0x4a>
    8404:	f8d6 0188 	ldr.w	r0, [r6, #392]	; 0x188
    8408:	fa09 f105 	lsl.w	r1, r9, r5
    840c:	f8d6 b004 	ldr.w	fp, [r6, #4]
    8410:	4201      	tst	r1, r0
    8412:	d10b      	bne.n	842c <__call_exitprocs+0x9c>
    8414:	4790      	blx	r2
    8416:	6872      	ldr	r2, [r6, #4]
    8418:	455a      	cmp	r2, fp
    841a:	d112      	bne.n	8442 <__call_exitprocs+0xb2>
    841c:	f8d8 3148 	ldr.w	r3, [r8, #328]	; 0x148
    8420:	42b3      	cmp	r3, r6
    8422:	d0da      	beq.n	83da <__call_exitprocs+0x4a>
    8424:	461e      	mov	r6, r3
    8426:	2e00      	cmp	r6, #0
    8428:	d1cc      	bne.n	83c4 <__call_exitprocs+0x34>
    842a:	e7da      	b.n	83e2 <__call_exitprocs+0x52>
    842c:	f8d6 018c 	ldr.w	r0, [r6, #396]	; 0x18c
    8430:	4201      	tst	r1, r0
    8432:	d10b      	bne.n	844c <__call_exitprocs+0xbc>
    8434:	f8d4 1080 	ldr.w	r1, [r4, #128]	; 0x80
    8438:	9800      	ldr	r0, [sp, #0]
    843a:	4790      	blx	r2
    843c:	6872      	ldr	r2, [r6, #4]
    843e:	455a      	cmp	r2, fp
    8440:	d0ec      	beq.n	841c <__call_exitprocs+0x8c>
    8442:	f8d8 6148 	ldr.w	r6, [r8, #328]	; 0x148
    8446:	2e00      	cmp	r6, #0
    8448:	d1bc      	bne.n	83c4 <__call_exitprocs+0x34>
    844a:	e7ca      	b.n	83e2 <__call_exitprocs+0x52>
    844c:	f8d4 0080 	ldr.w	r0, [r4, #128]	; 0x80
    8450:	4790      	blx	r2
    8452:	e7e0      	b.n	8416 <__call_exitprocs+0x86>

00008454 <atexit>:
    8454:	2300      	movs	r3, #0
    8456:	4601      	mov	r1, r0
    8458:	461a      	mov	r2, r3
    845a:	4618      	mov	r0, r3
    845c:	f000 b82a 	b.w	84b4 <__register_exitproc>

00008460 <__libc_fini_array>:
    8460:	b538      	push	{r3, r4, r5, lr}
    8462:	f248 55e0 	movw	r5, #34272	; 0x85e0
    8466:	f2c0 0501 	movt	r5, #1
    846a:	f248 54dc 	movw	r4, #34268	; 0x85dc
    846e:	f2c0 0401 	movt	r4, #1
    8472:	1b2c      	subs	r4, r5, r4
    8474:	10a4      	asrs	r4, r4, #2
    8476:	d005      	beq.n	8484 <__libc_fini_array+0x24>
    8478:	f855 3d04 	ldr.w	r3, [r5, #-4]!
    847c:	3c01      	subs	r4, #1
    847e:	4798      	blx	r3
    8480:	2c00      	cmp	r4, #0
    8482:	d1f9      	bne.n	8478 <__libc_fini_array+0x18>
    8484:	e8bd 4038 	ldmia.w	sp!, {r3, r4, r5, lr}
    8488:	f000 b85a 	b.w	8540 <_fini>

0000848c <__retarget_lock_init>:
    848c:	4770      	bx	lr
    848e:	bf00      	nop

00008490 <__retarget_lock_init_recursive>:
    8490:	4770      	bx	lr
    8492:	bf00      	nop

00008494 <__retarget_lock_close>:
    8494:	4770      	bx	lr
    8496:	bf00      	nop

00008498 <__retarget_lock_close_recursive>:
    8498:	4770      	bx	lr
    849a:	bf00      	nop

0000849c <__retarget_lock_acquire>:
    849c:	4770      	bx	lr
    849e:	bf00      	nop

000084a0 <__retarget_lock_acquire_recursive>:
    84a0:	4770      	bx	lr
    84a2:	bf00      	nop

000084a4 <__retarget_lock_try_acquire>:
    84a4:	2001      	movs	r0, #1
    84a6:	4770      	bx	lr

000084a8 <__retarget_lock_try_acquire_recursive>:
    84a8:	2001      	movs	r0, #1
    84aa:	4770      	bx	lr

000084ac <__retarget_lock_release>:
    84ac:	4770      	bx	lr
    84ae:	bf00      	nop

000084b0 <__retarget_lock_release_recursive>:
    84b0:	4770      	bx	lr
    84b2:	bf00      	nop

000084b4 <__register_exitproc>:
    84b4:	e92d 47f0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
    84b8:	f648 2610 	movw	r6, #35344	; 0x8a10
    84bc:	f2c0 0601 	movt	r6, #1
    84c0:	4607      	mov	r7, r0
    84c2:	4699      	mov	r9, r3
    84c4:	4688      	mov	r8, r1
    84c6:	4692      	mov	sl, r2
    84c8:	6830      	ldr	r0, [r6, #0]
    84ca:	f7ff ffe9 	bl	84a0 <__retarget_lock_acquire_recursive>
    84ce:	f248 50a0 	movw	r0, #34208	; 0x85a0
    84d2:	f2c0 0000 	movt	r0, #0
    84d6:	6803      	ldr	r3, [r0, #0]
    84d8:	f8d3 4148 	ldr.w	r4, [r3, #328]	; 0x148
    84dc:	b32c      	cbz	r4, 852a <__register_exitproc+0x76>
    84de:	6865      	ldr	r5, [r4, #4]
    84e0:	2d1f      	cmp	r5, #31
    84e2:	dc27      	bgt.n	8534 <__register_exitproc+0x80>
    84e4:	b957      	cbnz	r7, 84fc <__register_exitproc+0x48>
    84e6:	1c6b      	adds	r3, r5, #1
    84e8:	3502      	adds	r5, #2
    84ea:	6830      	ldr	r0, [r6, #0]
    84ec:	6063      	str	r3, [r4, #4]
    84ee:	f844 8025 	str.w	r8, [r4, r5, lsl #2]
    84f2:	f7ff ffdd 	bl	84b0 <__retarget_lock_release_recursive>
    84f6:	2000      	movs	r0, #0
    84f8:	e8bd 87f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, pc}
    84fc:	eb04 0185 	add.w	r1, r4, r5, lsl #2
    8500:	2301      	movs	r3, #1
    8502:	2f02      	cmp	r7, #2
    8504:	fa03 f305 	lsl.w	r3, r3, r5
    8508:	f8c1 a088 	str.w	sl, [r1, #136]	; 0x88
    850c:	f8d4 2188 	ldr.w	r2, [r4, #392]	; 0x188
    8510:	ea42 0203 	orr.w	r2, r2, r3
    8514:	f8c4 2188 	str.w	r2, [r4, #392]	; 0x188
    8518:	f8c1 9108 	str.w	r9, [r1, #264]	; 0x108
    851c:	bf02      	ittt	eq
    851e:	f8d4 218c 	ldreq.w	r2, [r4, #396]	; 0x18c
    8522:	4313      	orreq	r3, r2
    8524:	f8c4 318c 	streq.w	r3, [r4, #396]	; 0x18c
    8528:	e7dd      	b.n	84e6 <__register_exitproc+0x32>
    852a:	f503 74a6 	add.w	r4, r3, #332	; 0x14c
    852e:	f8c3 4148 	str.w	r4, [r3, #328]	; 0x148
    8532:	e7d4      	b.n	84de <__register_exitproc+0x2a>
    8534:	6830      	ldr	r0, [r6, #0]
    8536:	f7ff ffbb 	bl	84b0 <__retarget_lock_release_recursive>
    853a:	f04f 30ff 	mov.w	r0, #4294967295	; 0xffffffff
    853e:	e7db      	b.n	84f8 <__register_exitproc+0x44>

Disassembly of section .fini:

00008540 <_fini>:
    8540:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
    8542:	bf00      	nop
    8544:	bcf8      	pop	{r3, r4, r5, r6, r7}
    8546:	bc08      	pop	{r3}
    8548:	469e      	mov	lr, r3
    854a:	4770      	bx	lr
