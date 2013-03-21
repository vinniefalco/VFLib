// Copyright (C) 2008 by Vinnie Falco, this file is part of VFLib.
// See the file LICENSE.txt for licensing information.

FPUFlags FPUFlags::getCurrent()
{
#if defined(_GNU_SOURCE) && defined(JUCE_GCC) //GCC Compiler
    FPUFlags flags;
    
    fpu_control_t controlWord = 0;
    _FPU_GETCW (controlWord);
    
    flags.setMaskNaNs        ((controlWord & _FPU_MASK_IM)    == _FPU_MASK_IM);
    flags.setMaskDenormals   ((controlWord & _FPU_MASK_DM)   == _FPU_MASK_DM);
    flags.setMaskZeroDivides ((controlWord & _FPU_MASK_ZM) == _FPU_MASK_ZM);
    flags.setMaskOverflows   ((controlWord & _FPU_MASK_OM)   == _FPU_MASK_OM);
    flags.setMaskUnderflows  ((controlWord & _FPU_MASK_UM)  == _FPU_MASK_UM);
    //flags.setMaskInexacts    ((controlWord & ?) == ?); //?
    //flags.setFlushDenormals  ((controlWord & ?) == ?); //?
    //flags.setInfinitySigned  ((controlWord & ?) == ?); //?
    
    //Get the rounding type:
    Rounding rounding = roundDown;
    
    switch (fegetround())
    {
        case _FPU_RC_ZERO:      rounding = roundChop; break;
        case _FPU_RC_UP:        rounding = roundUp;   break;
        case _FPU_RC_DOWN:      rounding = roundDown; break;
        case _FPU_RC_NEAREST:   rounding = roundNear; break;
        case _FPU_RESERVED: /*Do extra stuff?*/ break;
        default:
          Throw (std::runtime_error ("Unknown rounding mode found in fegetround()!"));
    };
    
    flags.setRounding (rounding);
    
    //Get the floating-point precision:
    Precision precision = bits64;
    
    switch (controlWord)
    {
        case _FPU_EXTENDED: precision = bits64; break;
        case _FPU_DOUBLE:   precision = bits53; break;
        case _FPU_SINGLE:   precision = bits24; break;
        default:
          Throw (std::runtime_error ("Unknown precision found in _FPU_GETCW()!"));
    };

    flags.setPrecision (precision);
    
    return flags;
#else
    #pragma message(VF_LOC_"Missing platform-specific implementation")
    
    return FPUFlags();
#endif
}

static void setControl (const FPUFlags::Flag& flag,
                        fpu_control_t& control,
                        const unsigned int constant)
{
    if (flag.is_set() && flag.value())
    {
        control |= constant;
    }
}

void FPUFlags::setCurrent (const FPUFlags& flags)
{
#if defined(_GNU_SOURCE) && defined(JUCE_GCC)
    fpu_control_t newControl = 0;

    setControl (flags.getMaskNaNs(), newControl, _FPU_MASK_IM);
    setControl (flags.getMaskDenormals(), newControl, _FPU_MASK_DM);
    setControl (flags.getMaskZeroDivides(), newControl, _FPU_MASK_ZM);
    setControl (flags.getMaskOverflows(), newControl, _FPU_MASK_OM);
    setControl (flags.getMaskUnderflows(), newControl, _FPU_MASK_UM);
    //setControl (flags.getMaskInexacts(), newControl, ?); //?
    //setControl (flags.getFlushDenormals(), newControl, ?); //?
    //setControl (flags.getInfinitySigned(), newControl, ?); //?

    if (flags.getRounding().is_set())
    {
        const Rounding rounding = flags.getRounding().value();

        switch (rounding)
        {
            case roundChop: newControl |= _FPU_RC_ZERO; break;
            case roundUp:   newControl |= _FPU_RC_UP;   break;
            case roundDown: newControl |= _FPU_RC_DOWN; break;
            case roundNear: newControl |= _FPU_RC_NEAREST; break;
        }
    }

    if (flags.getPrecision().is_set())
    {
        switch (flags.getPrecision().value())
        {
            case bits64: newControl |= _FPU_EXTENDED; break;
            case bits53: newControl |= _FPU_DOUBLE; break;
            case bits24: newControl |= _FPU_SINGLE; break;
        }
    }

   _FPU_SETCW (newControl);
#else
    (void) flags; //Prevents useless warning
#endif
}