#pragma once
#include "stdafx.h"
#include "SpecialVH264Dlg.h"

char* probe_nal_unit(char* filename, int data_offset, int data_length);
int h264_analyze(int argc, char* argv[]);
