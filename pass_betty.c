#include <unistd.h>
/**
*team_members - fuction that write the team members
*Return: nothing
*/
void team_members(void);

void team_members(void)
{
	write(1, "Abel and Oletilwe\n", 18);
}

/**
* main - entry point
* Return: nothing
*/
int main(void)
{
team_members();
return (0);
}
