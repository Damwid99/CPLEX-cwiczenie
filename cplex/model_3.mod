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
// Minimizacja sumy bezwzględnych odchyleń dla dopasowania krzywej kwadratowej
minimize sum(p in data) dev[p];
subject to {
  forall(p in data)
    dev[p] >= p.y - (c * p.x * p.x + b * p.x + a);
  forall(p in data)
    dev[p] >= -p.y + (c * p.x * p.x + b * p.x + a);
}