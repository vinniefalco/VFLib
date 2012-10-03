#include "ftextra.h"

FT_LOCAL_DEF( FT_UInt )
tt_face_get_kerning_pairs( TT_Face  face,
                          short*  glyph_pairs)
{
    FT_UInt   count, mask = 1;
    FT_Byte*  p       = face->kern_table;
    FT_Byte*  p_limit = p + face->kern_table_size;
    FT_UInt  total_pairs = 0;

    p   += 4;
    mask = 0x0001;

    for ( count = face->num_kern_tables;
          count > 0 && p + 6 <= p_limit;
          count--, mask <<= 1 )
    {
        FT_Byte* base     = p;
        FT_Byte* next     = base;
        FT_UInt  version  = FT_NEXT_USHORT( p );
        FT_UInt  length   = FT_NEXT_USHORT( p );
        FT_UInt  coverage = FT_NEXT_USHORT( p );
        FT_UInt  num_pairs;
        FT_Int   value    = 0;

        FT_UNUSED( version );

        next = base + length;

        if ( next > p_limit )  /* handle broken table */
            next = p_limit;

        if ( ( face->kern_avail_bits & mask ) == 0 )
            goto NextTable;

        if ( p + 8 > next )
            goto NextTable;

        num_pairs = FT_NEXT_USHORT( p );
        p        += 6;

        if ( ( next - p ) < 6 * (int)num_pairs )  /* handle broken count  */
            num_pairs = (FT_UInt)( ( next - p ) / 6 );

        switch ( coverage >> 8 )
        {
        case 0:
            {
                FT_UInt  count2;
                total_pairs += num_pairs;

                if (glyph_pairs)
                    for ( count2 = num_pairs; count2 > 0; count2-- )
                    {
                        FT_ULong  key = FT_NEXT_ULONG( p );

                        *glyph_pairs++ = (key >> 16); // left
                        *glyph_pairs++ = (short)key; // right

                        value = FT_PEEK_SHORT( p );
                    
                        *glyph_pairs++ = (short)value; 

                        p += 2;
                    }
            }
            break;

            /*
             *  We don't support format 2 because we haven't seen a single font
             *  using it in real life...
             */

        default:
            ;
        }

    NextTable:
        p = next;
    }

    return total_pairs;
}

static FT_UInt
tt_get_kerning_pairs( FT_Face     ttface,          /* TT_Face */
                      short*      pairs)
{
    TT_Face       face = (TT_Face)ttface;
    return tt_face_get_kerning_pairs( face, pairs);
}

FT_EXPORT_DEF( FT_Error )
FT_Get_Kerning_Pairs( FT_Face     face,
                      FT_UInt     kern_mode,
                      FT_UInt*    pair_count,
                      FT_Short**  kerns)
{
    FT_Error   error = FT_Err_Ok;
    FT_Driver  driver;

    if ( !face )
        return FT_Err_Invalid_Face_Handle;

    if ( !kerns  || !pair_count)
        return FT_Err_Invalid_Argument;

    *kerns = 0;
    *pair_count = 0;

    driver = face->driver;

    // be sure the interface is TT
    if ( driver->clazz->get_kerning == tt_get_kerning)
    {
        unsigned int i;
        FT_Short* kp = 0;

        // find out how many pairs we have
        FT_UInt n = tt_get_kerning_pairs( face, 0);

        if (n)
        {
            // allocate 6 shorts for each:
            // LEFT, RIGHT, VALUE
            kp = (FT_Short*)malloc(n*6*sizeof(FT_Short));
        }

        if (!kp)
            return error; // bail

        // now fill in the values
        tt_get_kerning_pairs(face, kp);

        // caller gets count & memory. NB: remember to free!
        *kerns = kp;
        *pair_count = n;
        
        for (i = 0; i < n; ++i)
        {
            int v = kp[2]; // value
            if ( kern_mode != FT_KERNING_UNSCALED )
            {
                v = FT_MulFix( v, face->size->metrics.x_scale );
                
                if ( kern_mode != FT_KERNING_UNFITTED )
                {
                    /* we scale down kerning values for small ppem values */
                    /* to avoid that rounding makes them too big.         */
                    /* `25' has been determined heuristically.            */
                    if ( face->size->metrics.x_ppem < 25 )
                        v = FT_MulDiv( v, face->size->metrics.x_ppem, 25 );

                    v = FT_PIX_ROUND( v);
                }
            }

            // clamp to range of signed short
            if (v < -32768) v = -32768;
            else if (v > 32767) v = 32767;

            // put it back
            kp[2] = (short)v;

            // to next entry
            kp += 3;
        }
    }

    return error;
}
