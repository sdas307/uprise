#include "xEngine.h"


/* ---------- Collision Functions ---------- */

// ------------------------------------------------------------
/*AABB (Axis-Aligned Bounding Box) collision.
     _________           _________
    |  rec1   |         |  rec2   |
    |_________|         |_________|

Collision exists unless one rectangle is completely:

1. Left  : rec1.right  <= rec2.left
2. Right : rec1.left   >= rec2.right
3. Above : rec1.bottom <= rec2.top
4. Below : rec1.top    >= rec2.bottom

We instead test for the opposite (overlap on both axes):

  rec1.left   < rec2.right
  rec1.right  > rec2.left
  rec1.top    < rec2.bottom
  rec1.bottom > rec2.top
*/
// ------------------------------------------------------------

bool xCheckCollisionAABB(xRectangle a, xRectangle b)
{
    return (
        a.x < b.x + b.width &&
        a.x + a.width > b.x &&
        a.y < b.y + b.height &&
        a.y + a.height > b.y
    );
}