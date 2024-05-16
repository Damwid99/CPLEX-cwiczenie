/*********************************************
 * OPL 22.1.1.0 Model
 * Author: 113505
 * Creation Date: 11 kwi 2024 at 09:50:20
 *********************************************/
tuple Point {
  float x;
  float y;
}
 
{Point} data = ...;
 
dvar float a;
dvar float b;
dvar float+ dev[data];
 

dvar float c;
//  Minimizacja maksymalnego odchylenia dla dopasowania krzywej kwadratowej
dvar float+ max_dev;
minimize max_dev;
subject to {
  forall(p in data)
    max_dev >= p.y - (c * p.x * p.x + b * p.x + a);
  forall(p in data)
    max_dev >= -p.y + (c * p.x * p.x + b * p.x + a);
}