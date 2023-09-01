package chipyard

import org.chipsalliance.cde.config.Config

// --------------
// Rocket+SHA3 Configs
// These live in a separate file to simplify patching out for the tutorials.
// --------------

// DOC include start: Sha3Rocket
class Sha3RocketConfig
    extends Config(
      new sha3.WithSha3Accel ++ // add SHA3 rocc accelerator
        new freechips.rocketchip.subsystem.WithNBigCores(1) ++
        new chipyard.config.AbstractConfig
    )
// DOC include end: Sha3Rocket

class Sha3RocketPrintfConfig
    extends Config(
      new sha3.WithSha3Printf ++
        new sha3.WithSha3Accel ++ // add SHA3 rocc accelerator
        new freechips.rocketchip.subsystem.WithNBigCores(1) ++
        new chipyard.config.AbstractConfig
    )
