package chipyard

import org.chipsalliance.cde.config.{Config}
import freechips.rocketchip.diplomacy.{AsynchronousCrossing}

// --------------
// Rocket+eFPGA Configs
// These live in a separate file to simplify deployment in other systems.
// --------------

class HazemConfig extends Config(
    new fpga.WithFPGA(use32Bit = false) ++                              // use SHA3BlackBox 64 bit instead of SHA3 32 bit (default)
    new freechips.rocketchip.subsystem.WithNBigCores(1) ++         // single rocket-core
    new freechips.rocketchip.subsystem.WithoutTLMonitors ++         // remove TL monitors for faster simulation
    new chipyard.config.AbstractConfig
)

class HazemConfig32Bit extends Config(
    new fpga.WithFPGA(use32Bit = true) ++                              // use SHA3BlackBox 32 bit instead of SHA3 64 bit
    new freechips.rocketchip.subsystem.WithNBigCores(1) ++         // single rocket-core
    new freechips.rocketchip.subsystem.WithoutTLMonitors ++         // remove TL monitors for faster simulation
    new chipyard.config.AbstractConfig
)