&x ≈ address_of (x)
*ptr ≈ deference (ptr)

address_of == inv (deference)

&*ptr == ptr
*&x == x


int x = 56;
int *ptr = &x; // say ptr == 0x7ffff930e95ac4b (an address)
               // also, say (int **ad_ptr = &ptr) == 0x7ffff930e95ac50

Q) simplify ' &(*(&(&(&(*(*(*(*(&(&(*(&(*ptr))))))))))))) ' to the smallest
   possible expression of * and / or & operators, assuming all dereferencings
   are valid.

A) &(x)
