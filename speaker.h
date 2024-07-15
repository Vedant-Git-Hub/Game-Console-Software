#ifndef H_SPEAKER_H
#define H_SPEAKER_H

#include <stdint.h>




#define SA_L	131
#define RE_K_L	139
#define RE_L	147
#define GA_K_L	156
#define GA_L	165
#define MA_L	175
#define MA_T_L	185
#define PA_L	196
#define DHA_K_L	208
#define DHA_L	220
#define NI_K_L	233
#define NI_L	247

#define SA_M	262
#define RE_K_M	277
#define RE_M	294
#define GA_K_M	311
#define GA_M	330
#define MA_M	349
#define MA_T_M	370
#define PA_M	392
#define DHA_K_M	415
#define DHA_M	440
#define NI_K_M	466
#define NI_M	494

#define SA_H	523
#define RE_K_H	554
#define RE_H	587
#define GA_K_H	622
#define GA_H	659
#define MA_H	698
#define MA_T_H	740
#define PA_H	784
#define DHA_K_H	831
#define DHA_H	880
#define NI_K_H	932
#define NI_H	998



void speaker_init(void);
void speaker_playTone(uint16_t );
void speaker_stop(void);

#endif
