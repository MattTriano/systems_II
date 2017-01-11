extern int start;
extern int stop;

int *addrOfStop = &stop;

int sum()
{
  int i;
  int total = 0;

  for (i = start; i <= *addrOfStop; i++)
    total += i;

  return(total);
}
