#
# rom_trace_analyzer_py : script to analyze STM32MP15 ROM code traces
# 

import os
import sys
import struct
import argparse

levels = (
    'INFO',
    'WARN',
    'ERR ',
    'DEBUG',
)

def level2str(level):
    try:
       return levels[level]
    except IndexError:
       return "UNKNOWN"


tags = {
   0x90000001 : "NAND_DetectionFailed",
   0x90000002 : "NAND_InitFailed",
   0x90000003 : "NAND_NotInitialized",
   0x90000004 : "NAND_NotOnfiOrNotDetected",
   0x90000005 : "NAND_TransferFailed",
   0x90000006 : "NAND_ImageTooBig",
   0x90000007 : "NAND_OnlyBadBlocks",
   0x90000008 : "NAND_UncorrectableEccErr",
   0x90000009 : "NAND_NotGPTFound",
   0x9000000A : "NAND_TryingSECBL1",
   0x9000000B : "NAND_TryingSECBL2",
   0x9000000C : "NAND_SecblFirstValidBlock",
   0x9000000E : "NAND_EccErrorsDetected",
   0x9000000F : "NAND_EccErrorCorrected",
   0x90000010 : "NAND_EccErrorNotInDataArea",
   0x90000011 : "NAND_SecblsFoundInGPT",
   0x90000012 : "NAND_ReadColAddr",
   0x90000013 : "NAND_ResetFailed",
   0x90000014 : "NAND_NoOnfiParameterPage",
   0x90000015 : "NAND_GetParamFromOtp",
   0x90000016 : "NAND_EccBitsNbForcedByOtp",
   0x90000017 : "NAND_NoValidBlockFound",
   0x90000018 : "NAND_GptFound",
   0x90000019 : "NAND_DirectFsblFound",
   0x9000001A : "NAND_TryingDirectFSBL",
   0x9000001B : "NAND_WrongFsblOffsetsInGPT",
   0x9000001C : "NAND_EndOfNandReached",
   0x90000101 : "NANDCORE_DetectionFailed",
   0x90000102 : "NANDCORE_InitFailed",
   0x90000103 : "NANDCORE_NotInitialized",
   0x90000104 : "NANDCORE_NotOnfiOrNotDetected",
   0x90000105 : "NANDCORE_TransferFailed",
   0x90000106 : "NANDCORE_ImageTooBig",
   0x90000107 : "NANDCORE_OnlyBadBlocks",
   0x90000108 : "NANDCORE_UncorrectableEccErr",
   0x90000109 : "NANDCORE_NotGPTFound",
   0x9000010A : "NANDCORE_TryingSECBL1",
   0x9000010B : "NANDCORE_TryingSECBL2",
   0x9000010E : "NANDCORE_EccErrorsDetected",
   0x9000010F : "NANDCORE_EccErrorCorrected",
   0x90000110 : "NANDCORE_EccErrorNotInDataArea",
   0x9000010C : "NANDCORE_SecblFirstValidBlock",
   0x90000111 : "NANDCORE_SecblsFoundInGPT",
   0x90000112 : "NANDCORE_ReadColAddr",
   0x90000113 : "NANDCORE_ResetFailed",
   0x90000114 : "NANDCORE_NoOnfiParameterPage",
   0x90000115 : "NANDCORE_GetParamFromOtp",
   0x90000116 : "NANDCORE_EccBitsNbForcedByOtp",
   0x90000117 : "NANDCORE_NoValidBlockFound",
   0x90000118 : "NANDCORE_GptFound",
   0x90000119 : "NANDCORE_DirectFsblFound",
   0x9000011A : "NANDCORE_TryingDirectFSBL",
   0x9000011B : "NANDCORE_WrongFsblOffsetsInGPT",
   0x9000011C : "NANDCORE_EndOfNandReached",
   0x9000020E : "FMC_NAND_LL_EccErrorsDetected",
   0x9000020F : "FMC_NAND_LL_EccErrorCorrected",
   0x90000210 : "FMC_NAND_LL_EccErrorNotInDataArea",
   0x90000251 : "QSPI_NAND_LL_NoEccErrorNoEccErrorOrCorrected",
   0x90000252 : "QSPI_NAND_LL_UncorrectableEccErr",
   0x40000001 : "MMC_AcknowledgeErr",
   0x40000002 : "MMC_AcknowledgeTimeout",
   0x40000003 : "MMC_CardNotDetected",
   0x40000004 : "MMC_DataCrcErr",
   0x40000005 : "MMC_DataTimeout",
   0x40000007 : "MMC_DmaTransferErr",
   0x40000008 : "MMC_CmdTimeoutErr",
   0x40000009 : "MMC_CmdCrcErr",
   0x4000000A : "MMC_AddAlignErr",
   0x4000000B : "MMC_NotEnoughBootDataRxErr",
   0x4000000C : "MMC_ImageCopiedIsNotComplete",
   0x4000000D : "MMC_ImageCopiedHeaderSizeZero",
   0x4000000E : "MMC_AttemptBootDespiteErrors",
   0x4000000F : "MMC_GotDataEndFlagWithNoErrors",
   0x40000010 : "MMC_NbBytesCopiedInSysram",
   0x40000011 : "MMC_ImageCopiedHeaderNotFound",
   0x80000001 : "QSPI_TryingSECBL1",
   0x80000002 : "QSPI_TryingSECBL2",
   0x80000003 : "QSPI_TryingSingleMode",
   0x80000004 : "QSPI_TryingDualMode",
   0x80000005 : "QSPI_FoundGpt",
   0x80000006 : "QSPI_FoundMagicAtDefaultLocation",
   0x80000007 : "QSPI_UseOffsets",
   0x80000008 : "QSPI_WrongImageLen",
   0x80000009 : "QSPI_Timeout",
   0x0000000A : "BOOTCORE_HwResetPOR",
   0x0000000B : "BOOTCORE_HwResetBOR",
   0x0000000C : "BOOTCORE_HwResetPadNrst",
   0x0000000D : "BOOTCORE_HwResetHcssRst",
   0x0000000E : "BOOTCORE_HwResetVCore",
   0x0000000F : "BOOTCORE_HwResetMpSysRst",
   0x00000010 : "BOOTCORE_HwResetMcSysRst",
   0x00000011 : "BOOTCORE_HwResetIwdg1",
   0x00000012 : "BOOTCORE_HwResetIwdg2",
   0x00000013 : "BOOTCORE_HwResetWwdg1",
   0x00000014 : "BOOTCORE_HwResetStdby",
   0x00000015 : "BOOTCORE_HwResetCStdby",
   0x00000016 : "BOOTCORE_HwResetMpu0Rst",
   0x00000017 : "BOOTCORE_HwResetMpu1Rst",
   0x00000018 : "BOOTCORE_HwResetInvalid",
   0x0000001A : "BOOTCORE_LogicalResetLocalMpuCore0Reset",
   0x0000001B : "BOOTCORE_LogicalResetRmaOrRmaRelockReq",
   0x0000001C : "BOOTCORE_LogicalResetCStdbyExit",
   0x0000001D : "BOOTCORE_LogicalResetStdbyExit",
   0x0000001E : "BOOTCORE_LogicalResetSystem",
   0x0000001F : "BOOTCORE_LogicalResetInvalid",
   0x00000025 : "BOOTCORE_ChipModeSecOpen",
   0x00000026 : "BOOTCORE_ChipModeSecOpenEngiBoot",
   0x00000027 : "BOOTCORE_ChipModeSecFinalNormal",
   0x00000028 : "BOOTCORE_ChipModeSecFinalRmaOngoing",
   0x00000029 : "BOOTCORE_ChipModeSecFinalRmaRelocked",
   0x0000002B : "BOOTCORE_ChipModeInvalid",
   0x00000031 : "BOOTCORE_BootActionLocalMpuCore0ResetProcess",
   0x00000037 : "BOOTCORE_BootActionRmaReqProcess",
   0x00000038 : "BOOTCORE_BootActionRmaProcess",
   0x00000039 : "BOOTCORE_BootActionRmaRelockReqProcess",
   0x0000003A : "BOOTCORE_BootActionColdBootProcess",
   0x0000003B : "BOOTCORE_BootActionWakeupCStdby",
   0x0000003C : "BOOTCORE_BootActionWakeupStdby",
   0x0000003D : "BOOTCORE_BootActionInvalid",
   0x0000003E : "BOOTCORE_BootActionEngiBoot",
   0x00000045 : "BOOTCORE_BootCfgOtpWordValue",
   0x00000046 : "BOOTCORE_BootCfgAfmuxOtpWord1Value",
   0x00000047 : "BOOTCORE_BootCfgAfmuxOtpWord2Value",
   0x00000048 : "BOOTCORE_BootCfgAfmuxOtpWord3Value",
   0x00000049 : "BOOTCORE_BootCfgHseValue",
   0x00000051 : "BOOTCORE_NoUsbDpPullupOtpBitValue",
   0x00000052 : "BOOTCORE_NoCpuPllOtpBitValue",
   0x00000061 : "BOOTCORE_ReOpenDebugValue",
   0x00000062 : "BOOTCORE_ReOpenSecNSecDebugValue",
   0x00000063 : "BOOTCORE_ReOpenSecOnlyDebugValue",
   0x00000064 : "BOOTCORE_ReOpenDbgSwEnableAndHdp",
   0x00000065 : "BOOTCORE_DebugCloseAllButDbgenAndDeviceen",
   0x00000066 : "BOOTCORE_RmaOtpWordValue",
   0x00000068 : "BOOTCORE_RmaTrialOver",
   0x00000069 : "BOOTCORE_RmaTrialFoundFreeFuseBit",
   0x0000006A : "BOOTCORE_FusedNewRmaTrial",
   0x0000006B : "BOOTCORE_RmaPasswdMatch",
   0x0000006C : "BOOTCORE_RmaPasswdError",
   0x0000006D : "BOOTCORE_RmaRequestValue",
   0x0000006E : "BOOTCORE_RmaStatusValue",
   0x0000006F : "BOOTCORE_RmaRelockTrialOver",
   0x00000070 : "BOOTCORE_RmaRelockTrialCurrentNb",
   0x00000071 : "BOOTCORE_FusedNewRmaRelockTrial",
   0x00000072 : "BOOTCORE_RmaRelockPasswdMatch",
   0x00000073 : "BOOTCORE_RmaRelockPasswdError",
   0x00000074 : "BOOTCORE_NoDataCacheBitValue",
   0x00000075 : "BOOTCORE_WakeupFromCSTANDBY",
   0x00000076 : "BOOTCORE_WakeupFromSTANDBY",
   0x00000077 : "BOOTCORE_WakeupFromSTANDBYMpuBenMcuBen",
   0x00000078 : "BOOTCORE_WakeupFromSTANDBYMcuSecPerimeterRccTzenRccMckProt",
   0x00000079 : "BOOTCORE_WkUpActiveFlags",
   0x0000007A : "BOOTCORE_McuRestartOk",
   0x0000007B : "BOOTCORE_McuRestartKoNoHashWhileMandatory",
   0x0000007C : "BOOTCORE_McuRestartKoWrongHash",
   0x0000007D : "BOOTCORE_McuMcicOutOfRangeHashReq",
   0x0000007E : "BOOTCORE_McuMcicHashDrvCallStart",
   0x0000007F : "BOOTCORE_McuRestartKoErrorWhileHashing",
   0x00000080 : "BOOTCORE_McuMcicHashFailStart",
   0x00000081 : "BOOTCORE_McuMcicHashFailFinish",
   0x00000082 : "BOOTCORE_McuCodeHashVerifReq",
   0x00000083 : "BOOTCORE_McuNoCodeHashVerifReq",
   0x00000084 : "BOOTCORE_McuCodeHashVerifPass",
   0x00000085 : "BOOTCORE_McuSecurityPerimeterVerifPass",
   0x00000086 : "BOOTCORE_McuSecurityPerimeterVerifFailed",
   0x00000087 : "BOOTCORE_McuSecurityPerimeterVerifNotChecked",
   0x00000088 : "BOOTCORE_WakeupFromCSTANDBYWithMcuNotRunning",
   0x00000089 : "BOOTCORE_WakeupFromCSTANDBYWithMcuRunning",
   0x0000008A : "BOOTCORE_WakeupFromCSTANDBYWithMcuSev",
   0x0000008B : "BOOTCORE_WakeupFromCSTANDBYWithWwdg1Evt",
   0x00000091 : "BOOTCORE_MpuCpuPowerStateHasBeenInCStandby",
   0x00000092 : "BOOTCORE_SystemPowerStateHasBeenInStandby",
   0x00000093 : "BOOTCORE_BootModeNOBOOTENGIBOOT",
   0x00000094 : "BOOTCORE_BootModeNOBOOTNOTENGIBOOTREQBYBOOTPINS",
   0x00000095 : "BOOTCORE_BootModeNOBOOT",
   0x00000096 : "BOOTCORE_BootModeNOBOOTWITHENGIACCESS",
   0x00000097 : "BOOTCORE_BootModeNOBOOTCSTANDBY",
   0x00000098 : "BOOTCORE_BootModeCOLDBOOT",
   0x00000099 : "BOOTCORE_WakeupFromCSTANDBYMcuSysRstReqEvt",
   0x000000BF : "BOOTCORE_BootTimerSrcSoftCnt",
   0x000000C0 : "BOOTCORE_BootTimerSrcGenTimer",
   0x000000CF : "BOOTCORE_OtpBootSrcDisableMaskVal",
   0x000000D0 : "BOOTCORE_OtpBootUartInstanceDisableMaskVal",
   0x000000D1 : "BOOTCORE_EnabledSrcMaskVal",
   0x000000E0 : "BOOTCORE_CSISwitchON",
   0x000000E8 : "BOOTCORE_SafMemPwrUp",
   0x000000E9 : "BOOTCORE_SafMemPwrDown",
   0x000000EA : "BOOTCORE_FreezeIWDG12Clocks",
   0x000000EB : "BOOTCORE_UnFreezeIWDG12Clocks",
   0x000000ED : "BOOTCORE_BootFAILED",
   0x00000120 : "BOOTCORE_UartTraceEntryOnHwInstance",
   0x00000132 : "BOOTCORE_Pll12StartDisabledByOtpBit",
   0x00000133 : "BOOTCORE_Pll12StartNotDisabledByOtpBit",
   0x00000134 : "BOOTCORE_Pll1Started",
   0x00000135 : "BOOTCORE_Pll1Locked",
   0x00000136 : "BOOTCORE_Pll1LockTimeout",
   0x00000137 : "BOOTCORE_CkMpuSsSwitchedOnPll1",
   0x00000138 : "BOOTCORE_Pll2Started",
   0x00000139 : "BOOTCORE_Pll2Locked",
   0x0000013A : "BOOTCORE_Pll2LockTimeout",
   0x0000013B : "BOOTCORE_CkAxiSsSwitchedOnPll2",
   0x0000013C : "BOOTCORE_Pll12StartReqStatusPllNotStarted",
   0x0000013D : "BOOTCORE_Pll12StartReqStatusPllStarted",
   0x00000140 : "BOOTCORE_BootSrcPeriphLoadLoopDisabled",
   0x0000014E : "BOOTCORE_Pll4Started",
   0x0000014F : "BOOTCORE_Pll4Locked",
   0x00000150 : "BOOTCORE_Pll4LockTimeout",
   0x00000151 : "BOOTCORE_HseNotReady",
   0x00000152 : "BOOTCORE_StartupWaitTime",
   0x00000153 : "BOOTCORE_PllUsbLocked",
   0x00000154 : "BOOTCORE_PllUsbLockTimeout",
   0x00000155 : "BOOTCORE_BootRomVer",
   0x00000156 : "BOOTCORE_BootRomChipVer",
   0x00000157 : "BOOTCORE_BootRomCutVer",
   0x00000158 : "BOOTCORE_BootRomForRtlVer",
   0x00000159 : "BOOTCORE_BootRomTargetPlatform",
   0x0000015A : "BOOTCORE_BootRomMaskVer",
   0x0000015D : "BOOTCORE_McuSecPerimeterRccTzenValue",
   0x0000015E : "BOOTCORE_McuSecPerimeterMckprotValue",
   0x0000015F : "BOOTCORE_McuSecPerimeterExtiTzenr1Value",
   0x00000160 : "BOOTCORE_McuSecPerimeterExtiTzenr2Value",
   0x00000161 : "BOOTCORE_McuSecPerimeterExtiTzenr3Value",
   0x00000162 : "BOOTCORE_McuMcicReadInTampOffsetInBytesOfCodeToHashInRETRAM",
   0x00000163 : "BOOTCORE_McuMcicReadInTampSizeInBytesToHash",
   0x00000164 : "BOOTCORE_McuMcicReadInTampSignatureWord",
   0x00000165 : "BOOTCORE_McuSecPerimeterReadWriteSecureOnlyLastBackupIdx",
   0x00000166 : "BOOTCORE_McuSecPerimeterWriteSecureOnlyLastBackupIdx",
   0x00000167 : "BOOTCORE_BootModeNOBOOTWithSignalingFromNsec",
   0x00000168 : "BOOTCORE_NoBootTogglePa13Nsec",
   0x00000169 : "BOOTCORE_McuSecPerimeterTampSmcrVal",
   0x0000017D : "BOOTCORE_BootModeENGIBOOTSysRamAllNsecInTZMA1",
   0x00001000 : "BOOTCORE_BootPinsFirstSelNone",
   0x00001001 : "BOOTCORE_BootPinsFirstSelSerial",
   0x00001002 : "BOOTCORE_BootPinsFirstSelQspiNor",
   0x00001003 : "BOOTCORE_BootPinsFirstSelSd",
   0x00001004 : "BOOTCORE_BootPinsFirstSelEmmc",
   0x00001005 : "BOOTCORE_BootPinsFirstSelFmc",
   0x00001006 : "BOOTCORE_BootPinsFirstSelEngiBoot",
   0x00001007 : "BOOTCORE_BootPinsFirstSelUnknown",
   0x00001008 : "BOOTCORE_BootPinsOverridesOtp",
   0x00001017 : "BOOTCORE_BootPinsFirstSelQspiNand",
   0x00001009 : "BOOTCORE_OtpPrimarySrcForceFmc",
   0x0000100A : "BOOTCORE_OtpPrimarySrcForceQspiNor",
   0x0000100B : "BOOTCORE_OtpPrimarySrcForceEmmc",
   0x0000100C : "BOOTCORE_OtpPrimarySrcForceSd",
   0x0000100D : "BOOTCORE_OtpPrimarySrcForceQspiNand",
   0x0000100E : "BOOTCORE_OtpPrimarySrcForceNothing",
   0x0000100F : "BOOTCORE_OtpPrimarySrcForceUnknown",
   0x00001010 : "BOOTCORE_OtpSecondarySrcForceFmc",
   0x00001011 : "BOOTCORE_OtpSecondarySrcForceQspiNand",
   0x00001012 : "BOOTCORE_OtpSecondarySrcForceQspiNor",
   0x00001013 : "BOOTCORE_OtpSecondarySrcForceEmmc",
   0x00001014 : "BOOTCORE_OtpSecondarySrcForceSd",
   0x00001015 : "BOOTCORE_OtpSecondarySrcForceNothing",
   0x00001016 : "BOOTCORE_OtpSecondarySrcForceUnknown",
   0x00001020 : "BOOTCORE_TampForceSerialBoot",
   0x00002001 : "BOOTCORE_AuthWrongImageVersion",
   0x00002002 : "BOOTCORE_AuthHashAreaStartAdd",
   0x00002003 : "BOOTCORE_AuthImageLength",
   0x00002004 : "BOOTCORE_AuthImageSizeToHash",
   0x00002005 : "BOOTCORE_AuthImageEntryPoint",
   0x00002006 : "BOOTCORE_AuthEccAlgoP256NIST",
   0x00002007 : "BOOTCORE_AuthEccAlgoBrainPool256",
   0x00002008 : "BOOTCORE_AuthEccAlgoUnknown",
   0x00002009 : "BOOTCORE_AuthNoSigCheckValue",
   0x0000200A : "BOOTCORE_AuthEntryPointOutOfRange",
   0x0000200B : "BOOTCORE_AuthPubKHashFailStart",
   0x0000200C : "BOOTCORE_AuthPubKHashFailFinish",
   0x0000200D : "BOOTCORE_AuthPubKHashCompareError",
   0x0000200E : "BOOTCORE_AuthPubKHashCompareOk",
   0x0000200F : "BOOTCORE_AuthImageHashFailStart",
   0x00002010 : "BOOTCORE_AuthImageHashFailFinish",
   0x00002011 : "BOOTCORE_AuthImageSignatureFromHeaderECCDecryptStarted",
   0x00002012 : "BOOTCORE_AuthImageSignatureKo",
   0x00002013 : "BOOTCORE_AuthImageSignatureOk",
   0x00002014 : "BOOTCORE_AuthDecisionIsJumpToImage",
   0x00002015 : "BOOTCORE_AuthWrongImageHeaderVersion",
   0x00002016 : "BOOTCORE_AuthWrongMagicNumber",
   0x00002017 : "BOOTCORE_AuthImageLengthTooSmall",
   0x00002018 : "BOOTCORE_AuthImageLengthTooBig",
   0x00002019 : "BOOTCORE_AuthWrongImageChecksum",
   0x0000201A : "BOOTCORE_AuthIsAuthenticationMandatory",
   0x0000201B : "BOOTCORE_AuthIsAuthenticationSkipRequestedAndAllowed",
   0x00002400 : "BOOTCORE_HseFrequencyDetected",
   0x00002401 : "BOOTCORE_HseDigBypassDetected",
   0x00002402 : "BOOTCORE_HseAnalogBypassDetected",
   0x00002403 : "BOOTCORE_HseNoBypass",
   0x00002404 : "BOOTCORE_HseFreqDetectDisabled",
   0x00002405 : "BOOTCORE_HseBypassDetectDisabled",
   0x00002406 : "BOOTCORE_eMmcUseSingle128KBytesBootPartition",
   0x50000000 : "USB_Init",
   0x50000001 : "USB_Loop",
   0x50000002 : "USB_Selection",
   0x50000003 : "USB_CallingAuthAndGo",
   0x50000004 : "USB_DFU_OperationComplete",
   0x50000005 : "USB_DFU_GetStatus",
   0x50000006 : "USB_DFU_GetStatus_GoTo_Idle",
   0x50000007 : "USB_DFU_END_OF_DNLOAD",
   0x50000008 : "USB_DFU_DNLOAD",
   0x50000009 : "USB_DFU_UPLOAD",
   0x5000000A : "USB_DFU_GETSTATUS",
   0x5000000B : "USB_DFU_CLRSTATUS",
   0x5000000C : "USB_DFU_GETSTATE",
   0x5000000D : "USB_DFU_ABORT",
   0x5000000E : "USB_DFU_DETACH",
   0x5000000F : "USB_DFU_LEAVE",
   0x50000010 : "USB_DFU_DataOut",
   0x50000011 : "USB_DFU_GetStatusMedia",
   0x50000012 : "USB_DFU_SRAMWrite",
   0x50000013 : "USB_DFU_SRAMWrite_CRC",
   0x50000014 : "USB_DFU_SRAMWrite_imgL",
   0x50000015 : "USB_DFU_Init",
   0x50000016 : "USB_DFU_SET_INTERFACE",
   0x50000017 : "USB_DFU_SET_INTERFACE_ERR",
   0x50000018 : "USB_DFU_Get_INTERFACE",
   0x50000019 : "USB_DFU_LEAVE_EP0_TxReady",
   0x50000020 : "USB_ClockTree_Failed",
   0x50000021 : "USB_WrongDataTransfer",
   0x50000022 : "USB_DataTransfered",
   0x60000001 : "UART_Selection",
   0x60000002 : "UART_PeripheralSerialBootLoopStart",
   0x60000003 : "UART_PacketNumber",
   0x60000004 : "UART_PacketSize",
   0x60000005 : "UART_PacketXor",
   0x60000006 : "UART_ImageLength",
   0x60000008 : "UART_NACK",
   0x60000009 : "UART_ABORT",
   0x6000000A : "UART_ActivityDetected",
   0x6000000B : "UART_ActivityDetecting",
   0x30000001 : "SD_InitFailed",
   0x30000002 : "SD_TransferFailedDuringSecBlHeaderRead",
   0x30000003 : "SD_TransferFailedDuringSecBlPayloadRead",
   0x30000004 : "SD_CardDetected",
   0x30000005 : "SD_NoCardResponse",
   0x30000006 : "SD_TrySecBL1",
   0x30000007 : "SD_FailedSecBL1TrySecBL2",
   0x30000008 : "SD_InitDetailedErrorDesc",
   0x30000009 : "SD_ImageTooBig",
   0x3000000A : "SD_ImageLengthZero",
   0x3000000B : "SD_StdCapacityCardV11",
   0x3000000C : "SD_StdCapacityCardV20",
   0x3000000D : "SD_HighCapacityCardSDHCOrSDXC",
   0x3000000E : "SD_UnknownCapacityCard",
   0x3000000F : "SD_OverallRetryCnt",
   0x30000010 : "SD_ImageHeaderNotFound",
   0x30000011 : "SD_NotGPTFound",
   0x30000012 : "SD_FsblsFound",
   0x30000013 : "SD_GPTFound",
   0x30000014 : "SD_NotFSBLFound",
}

def tag2str(tag):
    try:
       return tags[tag]
    except KeyError:
       return None


class Trace(object):

    def __init__(self, timestamp, level, tag, data ):
        self.timestamp = timestamp
        self.level = level
        self.tag = tag
        self.data = data

    def dump(self):
        level_str = level2str(self.level)
        tag_str = tag2str(self.tag)

        if tag_str: 
           print( "< @ %08d | [%s] - %s" % (self.timestamp, level_str, tag_str), end='' )

           if len(self.data) > 0:
              print (" (", end='')
              for d in self.data[:-1]:
                 print (" 0x%08X," % (d), end='')
              print (" 0x%08X )" % (self.data[-1]), end='')

           print (" >")

class TraceAnalyzer(object):
  
    START_WORD = 0xFFDDBB00

    def __init__(self):
       pass

    def _next_word_(self):
        word = self._file.read(4)
        if len(word):
           return struct.unpack('<L',word)[0]
        else:
           raise StopIteration('END OF FILE')

    def _look_for_start_word_(self):
       while True:
          if self._next_word_() == self.START_WORD:
             return True

    def parse(self,file_):
        self._file = file_
        return iter(self)

    def __iter__(self):
        return self

    def __next__(self):
        self._look_for_start_word_()

        size = self._next_word_()
        timestamp = self._next_word_()
        size -= 4
        level = self._next_word_()
        size -= 4
        tag = self._next_word_()
        size -= 4

        data = []
        while size > 0:
            data.append(self._next_word_())
            size -= 4

        return Trace(timestamp, level, tag, data)

if __name__ == '__main__':
    
    parser = argparse.ArgumentParser(description='STM32MPU15 Bootrom trace decoder')
    parser.add_argument("trace_file",  
          action="store",
          type=argparse.FileType('rb'),
          help="Name of binary trace file",
          metavar="FILE.BIN")
    
    args = parser.parse_args()

    traces_analyzer = TraceAnalyzer()
    traces = traces_analyzer.parse(args.trace_file)
    for trace in traces:
      trace.dump()

