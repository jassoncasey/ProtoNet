#ifndef PHASOR_H
#define PHASOR_H

namespace ProtoNet
{

extern "C"
{
    struct PhasorHdr
    {
        uint16_t sync:8;
        uint16_t resv1:1;
        uint16_t frame_type:3;
        uint16_t ver:4;
        
        uint16_t frame_size;

        uint16_t id_code;

        uint32_t soc;
        uint32_t frac_sec;
    };
}

}

#endif
