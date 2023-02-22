#if !defined(STRUCTS)
#define STRUCTS
#define HEIGHT 6
#define WIDTH 7
typedef enum {NONE, EQUALITY, AI_VICTORY, HU_VICTORY } end_e;
typedef enum {HUMAN, AI} player_e;
typedef enum {VOID, HU_CROSS, AI_ROUND} token_e;
typedef enum {ROBUST,FAST} strat_e;

#endif // STRUCTS
