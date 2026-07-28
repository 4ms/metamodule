import lauterbach.trace32.rcl as t32
from pathlib import Path

dbg = t32.connect()
basepath = Path(__file__).parent.parent
binpath = basepath / "build"/"main.uimg"
elfpath = basepath / "build"/"mp1corea7"/"medium"/"main.elf"

dbg.print(f"Flashing via python rcl {binpath}...")

dbg.cmd("system.mode down")
dbg.cmd("system.resetout")
dbg.cmd("wait 0.1")

dbg.cmd("SYStem.CPU STM32MP153D-CA7")
dbg.cmd("SYStem.config DEBUGPORTTYPE SWD")
dbg.cmd("SYStem.JtagClock 50MHz")
dbg.cmd("CORE.ASSIGN 1. 2.")

dbg.cmd("Trace.DISable")
dbg.cmd("SYStem.MemAccess DAP")
dbg.cmd("SYStem.attach")
dbg.cmd("break")

dbg.cmd(f"Data.LOAD.Binary {binpath} 0xC0000000 /DUALPORT")
dbg.cmd(f"Data.LOAD.Elf {elfpath} /CPP /NoCode")
dbg.cmd("PER.Set.simple AZSD:0x0:0x5C00A118 %Long 0xC0000000")

dbg.cmd("Go")

dbg.cmd("Trace.METHOD ONCHIP")
dbg.cmd("ETM.Trace ON")
dbg.cmd("ETM.ON")

dbg.cmd("Trace.arm")

