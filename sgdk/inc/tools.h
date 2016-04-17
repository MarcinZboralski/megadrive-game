/**
 *  \file tools.h
 *  \brief Misc tools methods
 *  \author Stephane Dallongeville
 *  \date 08/2011
 *
 * This unit provides some misc tools methods as getFPS(), unpack()...
 */

#ifndef _TOOLS_H_
#define _TOOLS_H_

#include "bmp.h"
#include "vdp_tile.h"
#include "vdp_bg.h"


/**
 *  \brief
 *      No compression.
 */
#define COMPRESSION_NONE        0
/**
 *  \brief
 *      Use aplib (appack or sixpack) compression scheme.
 */
#define COMPRESSION_APLIB       1
///**
// *  \brief
// *      Use Konami (lzkn1_pack) compression scheme.
// */
//#define COMPRESSION_LZKN        2
/**
 *  \brief
 *      Use RLE compression scheme.
 */
#define COMPRESSION_RLE         3
/**
 *  \brief
 *      Use RLE compression scheme adapted for Map data.
 */
#define COMPRESSION_MAP_RLE     4


/**
 *  \brief
 *      Returns number of Frame Per Second.
 *
 * This function actually returns the number of time it was called in the last second.<br>
 * i.e: for benchmarking you should call this method only once per frame update.
 */
u32 getFPS();
/**
 *  \brief
 *      Returns number of Frame Per Second (fix32 form).
 *
 * This function actually returns the number of time it was called in the last second.<br>
 * i.e: for benchmarking you should call this method only once per frame update.
 */
fix32 getFPS_f();


/**
 *  \brief
 *      KDebug log helper methods
 */
void KLog(char* text);
void KLog_U1(char* t1, u32 v1);
void KLog_U2(char* t1, u32 v1, char* t2, u32 v2);
void KLog_U3(char* t1, u32 v1, char* t2, u32 v2, char* t3, u32 v3);
void KLog_U4(char* t1, u32 v1, char* t2, u32 v2, char* t3, u32 v3, char* t4, u32 v4);
void KLog_U1x(u16 minSize, char* t1, u32 v1);
void KLog_U2x(u16 minSize, char* t1, u32 v1, char* t2, u32 v2);
void KLog_U3x(u16 minSize, char* t1, u32 v1, char* t2, u32 v2, char* t3, u32 v3);
void KLog_U4x(u16 minSize, char* t1, u32 v1, char* t2, u32 v2, char* t3, u32 v3, char* t4, u32 v4);
void KLog_S1(char* t1, s32 v1);
void KLog_S2(char* t1, s32 v1, char* t2, s32 v2);
void KLog_S3(char* t1, s32 v1, char* t2, s32 v2, char* t3, s32 v3);
void KLog_S4(char* t1, s32 v1, char* t2, s32 v2, char* t3, s32 v3, char* t4, s32 v4);
void KLog_S1x(u16 minSize, char* t1, s32 v1);
void KLog_S2x(u16 minSize, char* t1, s32 v1, char* t2, s32 v2);
void KLog_S3x(u16 minSize, char* t1, s32 v1, char* t2, s32 v2, char* t3, s32 v3);
void KLog_S4x(u16 minSize, char* t1, s32 v1, char* t2, s32 v2, char* t3, s32 v3, char* t4, s32 v4);
void KLog_f1(char* t1, fix16 v1);
void KLog_f2(char* t1, fix16 v1, char* t2, fix16 v2);
void KLog_f3(char* t1, fix16 v1, char* t2, fix16 v2, char* t3, fix16 v3);
void KLog_f4(char* t1, fix16 v1, char* t2, fix16 v2, char* t3, fix16 v3, char* t4, fix16 v4);
void KLog_f1x(s16 numDec, char* t1, fix16 v1);
void KLog_f2x(s16 numDec, char* t1, fix16 v1, char* t2, fix16 v2);
void KLog_f3x(s16 numDec, char* t1, fix16 v1, char* t2, fix16 v2, char* t3, fix16 v3);
void KLog_f4x(s16 numDec, char* t1, fix16 v1, char* t2, fix16 v2, char* t3, fix16 v3, char* t4, fix16 v4);
void KLog_F1(char* t1, fix32 v1);
void KLog_F2(char* t1, fix32 v1, char* t2, fix32 v2);
void KLog_F3(char* t1, fix32 v1, char* t2, fix32 v2, char* t3, fix32 v3);
void KLog_F4(char* t1, fix32 v1, char* t2, fix32 v2, char* t3, fix32 v3, char* t4, fix32 v4);
void KLog_F1x(s16 numDec, char* t1, fix32 v1);
void KLog_F2x(s16 numDec, char* t1, fix32 v1, char* t2, fix32 v2);
void KLog_F3x(s16 numDec, char* t1, fix32 v1, char* t2, fix32 v2, char* t3, fix32 v3);
void KLog_F4x(s16 numDec, char* t1, fix32 v1, char* t2, fix32 v2, char* t3, fix32 v3, char* t4, fix32 v4);


/**
 *  \brief
 *      Allocate a new Bitmap structure which can receive unpacked bitmap data of the specified Bitmap.<br/>
 *      If source is not packed the function only allocate space for simple shallow copy of the source.
 *
 *  \param bitmap
 *      Source Bitmap we want to allocate the unpacked Bitmap object.
 *  \return
 *      The new allocated Bitmap object which can receive the unpacked Bitmap, note that returned bitmap
 *      is allocated in a single bloc and can be released with Mem_Free(bitmap).<br/>
 *      <i>NULL</i> is returned if there is not enough memory to store the unpacked bitmap.
 */
Bitmap *allocateBitmap(const Bitmap *bitmap);
/**
 *  \brief
 *      Allocate a new Bitmap structure which can receive the bitmap data for the specified Bitmap dimension.
 *
 *  \param width
 *      Width in pixel of the bitmap structure we want to allocate.
 *  \param heigth
 *      heigth in pixel of the bitmap structure we want to allocate.
 *  \return
 *      The new allocated Bitmap object which can receive an unpacked Bitmap for the specified dimension.<br/>
 *      Note that returned bitmap is allocated in a single bloc and can be released with Mem_Free(bitmap).<br/>
 *      <i>NULL</i> is returned if there is not enough memory to allocate the bitmap.
 */
Bitmap *allocateBitmapEx(u16 width, u16 heigth);
/**
 *  \brief
 *      Allocate TileSet structure which can receive unpacked tiles data of the specified TileSet.<br/>
 *      If source is not packed the function only allocate space for simple shallow copy of the source.
 *
 *  \param tileset
 *      Source TileSet we want to allocate the unpacked TileSet object.
 *  \return
 *      The new allocated TileSet object which can receive the unpacked TileSet, note that returned tile set
 *      is allocated in a single bloc and can be released with Mem_Free(tb).<br/>
 *      <i>NULL</i> is returned if there is not enough memory to store the unpacked tiles.
 *      If the source TileSet is not packed then returned TileSet allocate only memory to do <i>NULL</i> is returned if there is not enough memory to store the unpacked tiles.
 */
TileSet *allocateTileSet(const TileSet *tileset);
/**
 *  \brief
 *      Allocate a new TileSet structure which can receive the data for the specified number of tile.
 *
 *  \param numTile
 *      Number of tile this tileset can contain
 *  \return
 *      The new allocated TileSet object which can receive the specified number of tile.<br/>
 *      Note that returned tileset is allocated in a single bloc and can be released with Mem_Free(tileset).<br/>
 *      <i>NULL</i> is returned if there is not enough memory to allocatee the tileset.
 */
TileSet *allocateTileSetEx(u16 numTile);
/**
 *  \brief
 *      Allocate Map structure which can receive unpacked map data of the specified Map.<br/>
 *      If source is not packed the function only allocate space for simple shallow copy of the source.
 *
 *  \param map
 *      Source Map we want to allocate the unpacked Map object.
 *  \return
 *      The new allocated Map object which can receive the unpacked Map, note that returned map
 *      is allocated in a single bloc and can be released with Mem_Free(map).<br/>
 *      <i>NULL</i> is returned if there is not enough memory to store the unpacked map.
 */
Map *allocateMap(const Map *map);
/**
 *  \brief
 *      Allocate a new Map structure which can receive map data for the specified Map dimension.
 *
 *  \param width
 *      Width in tile of the Map structure we want to allocate.
 *  \param heigth
 *      heigth in tile of the Map structure we want to allocate.
 *  \return
 *      The new allocated Map object which can receive data for the specified Map dimension.<br/>
 *      Note that returned map is allocated in a single bloc and can be released with Mem_Free(map).<br/>
 *      <i>NULL</i> is returned if there is not enough memory to allocate the map.
 */
Map *allocateMapEx(u16 width, u16 heigth);
/**
 *  \brief
 *      Allocate Image structure which can receive unpacked image data of the specified Image.
 *      If source is not packed the function only allocate space for simple shallow copy of the source.
 *
 *  \param image
 *      Source Image we want to allocate the unpacked Image object.
 *  \return
 *      The new allocated Image object which can receive the unpacked Image, note that returned image
 *      is allocated in a single bloc and can be released with Mem_Free(image).<br/>
 *      <i>NULL</i> is returned if there is not enough memory to store the unpacked image.
 */
Image *allocateImage(const Image *image);

/**
 *  \brief
 *      Convert the specified SubTileSet structure to TileSet.<br/>
 *      A SubTileSet is basically a sub set of a TileSet so this method will extract a part of the original tileset data
 *      and build a new TileSet out of it.<br/>
 *      If the original TileSet is compressed this method will unpack only the sub set of data and return them in an unpacked format.
 *
 *  \param subTileSet
 *      the SubTileSet to convert to TileSet.
 *  \param dest
 *      Destination TileSet where to store result, be sure to allocate a big enough TileSet to receive the result.<br/>
 *      If set to NULL then a dynamic allocated TileSet is returned.
 *  \return
 *      The extracted TileSet.<br/>
 *      If <i>dest</i> was set to NULL then the returned tileset is allocated in a single bloc and can be released with Mem_Free(tileset).<br/>
 *      <i>NULL</i> is returned if there is not enough memory to store the extracted tileset.
 */
TileSet *getTileSet(SubTileSet *subTileSet, TileSet *dest);

/**
 *  \brief
 *      Unpack the specified source Bitmap.
 *
 *  \param src
 *      bitmap to unpack.
 *  \param dest
 *      Destination bitmap where to store unpacked data, be sure to allocate enough space in image buffer.<br/>
 *      If set to NULL then a dynamic allocated Bitmap is returned.
 *  \return
 *      The unpacked Bitmap.<br/>
 *      If <i>dest</i> was set to NULL then the returned bitmap is allocated in a single bloc and can be released with Mem_Free(bitmap).<br/>
 *      <i>NULL</i> is returned if there is not enough memory to store the unpacked bitmap.
 */
Bitmap *unpackBitmap(const Bitmap *src, Bitmap *dest);
/**
 *  \brief
 *      Unpack the specified TileSet structure.
 *
 *  \param src
 *      tiles to unpack.
 *  \param dest
 *      Destination TileSet structure where to store unpacked data, be sure to allocate enough space in tiles and tilemap buffer.<br/>
 *      If set to NULL then a dynamic allocated TileSet is returned.
 *  \return
 *      The unpacked TileSet.<br/>
 *      If <i>dest</i> was set to NULL then the returned tiles base is allocated in a single bloc and can be released with Mem_Free(tb).<br/>
 *      <i>NULL</i> is returned if there is not enough memory to store the unpacked tiles.
 */
TileSet *unpackTileSet(const TileSet *src, TileSet *dest);
/**
 *  \brief
 *      Unpack the specified Map structure.
 *
 *  \param src
 *      map to unpack.
 *  \param dest
 *      Destination map where to store unpacked data, be sure to allocate enough space in tiles and tilemap buffer.<br/>
 *      If set to NULL then a dynamic allocated Map is returned.
 *  \return
 *      The unpacked Map.<br/>
 *      If <i>dest</i> was set to NULL then the returned map is allocated in a single bloc and can be released with Mem_Free(map).<br/>
 *      <i>NULL</i> is returned if there is not enough memory to store the unpacked map.
 */
Map *unpackMap(const Map *src, Map *dest);
/**
 *  \brief
 *      Unpack the specified Image structure.
 *
 *  \param src
 *       image to unpack.
 *  \param dest
 *      Destination Image where to store unpacked data.<br/>
 *      If set to NULL then a dynamic allocated Image is returned.
 *  \return
 *      The unpacked Image.<br/>
 *      If <i>dest</i> was set to NULL then the returned image is allocated in a single bloc and can be released with Mem_Free(image).<br/>
 *      <i>NULL</i> is returned if there is not enough memory to store the unpacked image.
 */
Image *unpackImage(const Image *src, Image *dest);

/**
 *  \brief
 *      Unpack a part of the specified source data buffer in the specified destination buffer.
 *
 *  \param compression
 *      compression type, accepted values:<br/>
 *      <b>COMPRESSION_NONE</b><br/>
 *      <b>COMPRESSION_APLIB</b><br/>
 *      <b>COMPRESSION_RLE</b><br/>
 *      <b>COMPRESSION_MAP_RLE</b><br/>
 *  \param src
 *      Source data buffer containing the packed data (aplib packer) to unpack.
 *  \param dest
 *      Destination buffer where to store unpacked data, be sure to allocate enough space.
 *  \param offset
 *      Source offset where to start decompression (0 means beginning).<br/>
 *      This offset may be expressed in 'unpacked' format then depending the compression scheme it will be internally adjusted.
 *  \param size
 *      Number of element (depend from compression model used) to unpack.<br/>
 *      If this parameter is set to <b>0</b> then the whole source buffer will be unpacked, in which case the offset parameter is assumed to be 0.
 *  \return
 *      FALSE if the operation failed (compression model does not support partial unpacking or no compression while 'size' parameter is set to 0)<br/>
 *      TRUE otherwise.
 */
u16 unpackEx(u16 compression, u8 *src, u8 *dest, u32 offset, u16 size);
/**
 *  \brief
 *      Unpack the specified source data buffer in the specified destination buffer.<br/>
 *      if source is not packed then nothing is done.
 *
 *  \param compression
 *      compression type, accepted values:<br/>
 *      <b>COMPRESSION_NONE</b><br/>
 *      <b>COMPRESSION_APLIB</b><br/>
 *      <b>COMPRESSION_RLE</b><br/>
 *      <b>COMPRESSION_MAP_RLE</b><br/>
 *  \param src
 *      Source data buffer containing the packed data (aplib packer) to unpack.
 *  \param dest
 *      Destination buffer where to store unpacked data, be sure to allocate enough space.
 */
void unpack(u16 compression, u8 *src, u8 *dest);

/**
 *  \brief
 *      Unpack (aplib packer) the specified source data buffer in the specified destination buffer.
 *
 *  \param src
 *      Source data buffer containing the packed data (aplib packer) to unpack.
 *  \param dest
 *      Destination buffer where to store unpacked data, be sure to allocate enough space.
 *  \return
 *      Unpacked size.
 */
u32 aplib_unpack(u8 *src, u8 *dest);
///**
// *  \brief
// *      Unpack (Konami packer) the specified source data buffer in the specified destination buffer.
// *
// *  \param src
// *      Source data buffer containing the packed data (Konami packer) to unpack.
// *  \param dest
// *      Destination buffer where to store unpacked data, be sure to allocate enough space.
// *  \return
// *      Unpacked size.
// */
//u32 lzkn_unpack(u8 *src, u8 *dest);
/**
 *  \brief
 *      Unpack (RLE 4bit packer based on Charles MacDonald code) the specified source data buffer in the specified destination buffer.
 *
 *  \param src
 *      Source data buffer containing the packed data (RLE 4bit packer) to unpack.
 *  \param dest
 *      Destination buffer where to store unpacked data, be sure to allocate enough space.
 *  \param offset
 *      Source offset (in byte) where to start decompression (0 means beginning of buffer).
 *  \param size
 *      Number of bloc to unpack.<br/>
 *      If this parameter is set to <b>0</b> then the whole source buffer will be unpacked, in which case the offset parameter is assumed to be 0.
 */
void rle4b_unpack(u8 *src, u8 *dest, u32 offset, u16 size);
/**
 *  \brief
 *      Unpack (RLE MAP packer) the specified source data buffer in the specified destination buffer.
 *
 *  \param src
 *      Source data buffer containing the packed data (RLE MAP packer) to unpack.
 *  \param dest
 *      Destination buffer where to store unpacked data, be sure to allocate enough space.
 *  \param offset
 *      Source offset (in byte) where to start decompression (0 means beginning of buffer).
 *  \param size
 *      Number of bloc to unpack.<br/>
 *      If this parameter is set to <b>0</b> then the whole source buffer will be unpacked, in which case the offset parameter is assumed to be 0.
 */
void rlemap_unpack(u8 *src, u8 *dest, u32 offset, u16 size);
/**
 *  \brief
 *      Unpack (RLE 4bit packer based on Charles MacDonald code) the specified source data buffer directly in VRAM.
 *
 *  \param src
 *      Source data buffer containing the packed data (RLE 4bit packer) to unpack.
 *  \param dest
 *      VRAM destination address where to store unpacked dat.
 *  \param offset
 *      Source offset (in byte) where to start decompression (0 means beginning of buffer).
 *  \param size
 *      Number of bloc to unpack.<br/>
 *      If this parameter is set to <b>0</b> then the whole source buffer will be unpacked, in which case the offset parameter is assumed to be 0.
 */
void rle4b_unpackVRam(u8 *src, u16 dest, u32 offset, u16 size);
/**
 *  \brief
 *      Decompresses tiles stored in UFTC format.<br/>
 *
 *   UFTC is a graphics compression format for the Mega Drive.<br/>
 *   Its purpose is to compress all the sprites making the animations of an object<br/>
 *   and be able to extract time in run-time (as the game is playing).<br/>
 *   It allows random access of tiles and it's pretty fast.<br/>
 *
 *  \param src
 *      Source data buffer containing the UFTC-compressed data
 *  \param dest
 *      Destination buffer where to store unpacked tiles
 *  \param index
 *      Index of first tile to decompress (counting from 0)
 *  \param cnt
 *      Number of tile to decompress
 *
 *  \author Javier Degirolmo (Sik)
 *  \date 2010
 */
void uftc_unpack(u8* src, u8 *dest, u16 index, u16 cnt);

/**
 *  \brief
 *      Decompresses data in raw deflate/zlib format.<br/>
 *
 *   zlib is a general-purpose compressor, supporting quite good
 *   compression ratios, but unpacking is relatively slow on the
 *   Genesis (around 23kb/s).
 *
 *  \param dest
 *      Destination buffer
 *  \param out_but_len
 *      Size of the destination buffer in bytes
 *  \param src
 *      Source data buffer containing compressed data
 *  \param src_buf_len
 *      Size of the source buffer in bytes
 */
int zlib_unpack(void *dest, const unsigned out_buf_len, const void *src, const unsigned src_buf_len);

#endif // _TOOLS_H_
