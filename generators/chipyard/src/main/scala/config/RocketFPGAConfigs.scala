package chipyard

import org.chipsalliance.cde.config.{Config}
import freechips.rocketchip.diplomacy.{AsynchronousCrossing}

// --------------
// Rocket+eFPGA Configs
// These live in a separate file to simplify deployment in other systems.
// --------------

class HazemConfig extends Config(
  new fpga.WithFPGA() ++                              // use FPGA FPGAMMIOChiselModule Module instead of FPGAMMIOBlackBox
  new freechips.rocketchip.subsystem.WithNBigCores(1) ++         // single rocket-core
  new freechips.rocketchip.subsystem.WithoutTLMonitors ++         // remove TL monitors for faster simulation
  new chipyard.config.AbstractConfig)

class HazemConfigBlackBox extends Config(
  new fpga.WithFPGA() ++                              // use FPGA FPGAMMIOBlackBox Module instead of FPGAMMIOChiselModule
  new freechips.rocketchip.subsystem.WithNBigCores(1) ++         // single rocket-core
  new freechips.rocketchip.subsystem.WithoutTLMonitors ++         // remove TL monitors for faster simulation
  new chipyard.config.AbstractConfig)
