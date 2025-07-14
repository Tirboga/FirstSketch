#define NOTE_L1  262
#define NOTE_L2  294
#define NOTE_L3  330
#define NOTE_L4  349
#define NOTE_L5  392
#define NOTE_L6  440
#define NOTE_L7  494
#define NOTE_M1  523
#define NOTE_M2  587
#define NOTE_M3  659
#define NOTE_M4  698
#define NOTE_M5  784
#define NOTE_M6  880
#define NOTE_M7  988
#define NOTE_H1  1046
#define NOTE_H2  1175
#define NOTE_H3  1318
#define NOTE_H4  1397
#define NOTE_H5  1568
#define NOTE_H6  1760
#define NOTE_H7  1976
//-------------------------------------------
//musical notation of Two Tigers 
const static int doubleTiger[] = { 
NOTE_M1,NOTE_M2,NOTE_M3,NOTE_M1, 
NOTE_M1,NOTE_M2,NOTE_M3,NOTE_M1, 
NOTE_M3,NOTE_M4,NOTE_M5, 
NOTE_M3,NOTE_M4,NOTE_M5, 
NOTE_M5,NOTE_M6,NOTE_M5,NOTE_M4,
NOTE_M3,NOTE_M1, 
NOTE_M5,NOTE_M6,NOTE_M5,NOTE_M4,
NOTE_M3,NOTE_M1, 
NOTE_M2,NOTE_L5,
NOTE_M1,0,
NOTE_M2,NOTE_L5,
NOTE_M1,0
};
//-------------------------------------------
const static int tempo[] = { 
2,2,2,2, 
2,2,2,2, 
2,2,1, 
2,2,1,  
2,2,2,2,
1,1,
2,2,2,2,
1,1,
1,1,
1,1,
1,1,
1,1
};