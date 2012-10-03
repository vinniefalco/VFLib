#ifndef __ftextra_h__
#define __ftextra_h__

FT_EXPORT_DEF( FT_Error )
FT_Get_Kerning_Pairs( FT_Face     face,
                      FT_UInt     kern_mode,
                      FT_UInt*    pair_count,
                      FT_Short**  kerns);


#endif // __ftextra_h__
