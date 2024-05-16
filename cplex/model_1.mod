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
 
// Minimizacja sumy bezwzględnych odchyleń dla dopasowania liniowego
minimize sum(p in data) dev[p];
subject to {
  forall(p in data)
    dev[p] >= p.y - (b * p.x + a);  // co najmniej równy różnicy między rzeczywistą wartością y a wartością wyznaczoną dla prostej
  forall(p in data)
    dev[p] >= -p.y + (b * p.x + a);
}