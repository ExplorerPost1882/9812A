/*vex-vision-config:begin*/
#include "vex.h"
vex::vision::signature GREEN_CUBE = vex::vision::signature (1, -7615, -5439, -6526, -4045, -1727, -2886, 3, 0);
vex::vision::signature PURPLE_CUBE = vex::vision::signature (2, -1, 1505, 752, 6849, 9741, 8296, 3, 0);
vex::vision::signature ORANGE_CUBE = vex::vision::signature (3, 7041, 8823, 7932, -2995, -2103, -2548, 3, 0);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision Vision1 = vex::vision (vex::PORT1, 51, GREEN_CUBE, PURPLE_CUBE, ORANGE_CUBE, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/