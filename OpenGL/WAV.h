#pragma once
#include <iostream>
#include <fstream>

typedef struct WAV_HEADER wav_hdr;

void WAV_save(const short* data, const double size, char* musicFileName);

//void WAV_save(const double* data, const long long size, char* musicFileName) {
//    static_assert(sizeof(wav_hdr) == 44, "");
//
//    //std::string in_name = "test.bin"; // raw pcm data without wave header
//    //std::ifstream in(in_name, std::ifstream::binary);
//    //
//    //uint32_t fsize = in.tellg();
//    //in.seekg(0, std::ios::end);
//    //fsize = (uint32_t)in.tellg() - fsize;
//    //in.seekg(0, std::ios::beg);
//    //
//    //printf("file size: %u\n", fsize);
//
//    wav_hdr wav;
//    wav.ChunkSize = size + sizeof(wav_hdr) - 8;
//    wav.Subchunk2Size = size + sizeof(wav_hdr) - 44;
//
//    std::ofstream out(musicFileName, std::ios::binary);
//    out.write(reinterpret_cast<const char*>(&wav), sizeof(wav));
//
//    //unsigned short int d;
//    for (int i = 0; i < size; ++i) {
//        // TODO: read/write in blocks
//        //in.read(reinterpret_cast<char*>(&d), sizeof(int16_t));
//        int16_t Data = int16_t(data[i]);
//
//        out.write(reinterpret_cast<char*>(&Data), sizeof(int16_t));
//    }
//
//}