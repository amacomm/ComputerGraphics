#pragma once
#include "WAV.h"
#define S_RATE  (48000) //частота дискретизации
#define A_MAX (32000)

enum Signs{ Nope, Sharp, b};
enum Note{ C, CSharp, D, DSharp, E, F, FSharp, G, GSharp, A, ASharp, B };
enum Octave{ SubContra, Contra, Great, Small, FirstLine, SecondLine, TherdLine,	ForthLine};

class Music {
	double _size;
	short* _data;
	float HrNote[12] = {0, 0.97, 2, 3.1, 4.25, 5.48, 6.78, 8.15, 9.61, 11.15, 12.79, 14.52  };
	int Ampl(double hz) {
		if (hz > 240 && hz < 290)return A_MAX;
		if (hz > 261.63) {
			return (3951 - 261.63) * A_MAX/2 / (hz - 261.63);
		}
		return ( 261.63-16.35) * A_MAX * 1 / (261.63-hz);
	}
public:
	Music():_size(0){}
	Music(int time): _size(16000 * 6*time) {
		_data = new short[_size];
		for (int i = 0, j = 0; i < _size; _data[i++] = 10000.0 * sin(2 * 3.14 * i / 96));
	}
	~Music() {
		_size = 0;
		if(_data)
			delete[] _data;
	}
	void AddNote(double time, double vol, Note note, Octave octave = Small) {
		_size += 16000.0 * 6.0*time;
		short* newData = new short[_size];
		int oct = std::pow(2, (int)octave);
		double s = oct * 16.35;
		s += oct * HrNote[note];
		for (int i = 0; i < _size - 16000.0 * 6.0*time; newData[i] = _data[i++]);
		for (int i = _size - 16000.0 * 6.0*time-1; i < _size-1; newData[i] = vol * A_MAX * sin(2*3.1416*i++ * s/S_RATE));
		if(_data)
			delete[] _data;
		_data = newData;
	}
	void AddTo(double offset, double time, double vol, Note note, Octave octave = Small) {
		int oct = std::pow(2, (int)octave);
		double s = oct * 16.35;
		s += oct * HrNote[note];
		for (int i = 16000 * 6 * offset; i < 16000 * 6 * (offset + time); i+=2) {
			_data[i] = vol * A_MAX * sin(2 * 3.1416 * i++ * s / S_RATE);
		}
	}
	
	void save(char* musicFileName) {
		WAV_save(_data, _size, musicFileName);
	}
};