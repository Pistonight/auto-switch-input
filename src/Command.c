#include <avr/pgmspace.h>
typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	X,
	Y,
	A,
	B,
	L,
	R,
	THROW,
	NOTHING,
	TRIGGERS
} Buttons_t;

typedef struct {
	Buttons_t button;
	uint16_t duration;
} command; 

static const command step[] = {
	// Setup controller
	{ NOTHING,  500},
	{ TRIGGERS,   10 },
	{ NOTHING,  300 },
	{ TRIGGERS,   10 },
	{ NOTHING,  300 },
	{ A,          10 },
	{ NOTHING,  500 },

	// Talk to Pondo
	{ A,          10 }, // Start
	{ NOTHING,   60 },
	{ B,          10 }, // Quick output of text
	{ NOTHING,   40 }, // Halloo, kiddums!
	{ A,          10 }, // <- I'll try it!
	{ NOTHING,   30 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ A,          10 }, // <- OK!
	{ NOTHING,   30 },
	{ B,          10 },
	{ NOTHING,   40 }, // Aha! Play bells are ringing! I gotta set up the pins, but I'll be back in a flurry
	{ A,          10 }, // <Continue>
	{ NOTHING,  650 }, // Cut to different scene (Knock 'em flat!)
	{ B,          10 },
	{ NOTHING,   40 },
	{ A,          10 }, // <Continue> // Camera transition takes place after this
	{ NOTHING,   100 },
	{ B,          10 },
	{ NOTHING,   40 }, // If you can knock over all 10 pins in one roll, that's a strike
	{ A,          10 }, // <Continue>
	{ NOTHING,   30 },
	{ B,          10 },
	{ NOTHING,   40 }, // A spare is...
	{ A,          10 }, // <Continue>
	{ NOTHING,  200 }, // Well, good luck
	{ A,          10 }, // <Continue>
	{ NOTHING,  300 }, // Pondo walks away

	// Pick up Snowball (Or alternatively, run to bail in case of a non-strike)
	{ A,          10 },
	{ NOTHING,   100 },
	{ LEFT,      84 },
	{ UP,        160 },
	{ THROW,     50 },

	// Non-strike alternative flow, cancel bail and rethrow
	{ NOTHING,   60 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 }, // I have to split dialogue (It's nothing)
	{ NOTHING,   30 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,  900 },
	{ B,          10 }, // Snowly moly... there are rules!
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 }, // Second dialogue
	{ NOTHING,   40 },
	{ DOWN,      20 }, // Return to snowball
	{ NOTHING,   40 },
	{ A,          10 }, // Pick up snowball, we just aimlessly throw it
	{ NOTHING,   100 },
	{ UP,        20 },
	{ THROW,     50 },

	// Back at main flow
	{ NOTHING,  350 }, // Ater throw wait
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 }, // To the rewards
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	
	{ B,          10 }, // Wait for 450 cycles by bashing B (Like real players do!)
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 },
	{ B,          10 },
	{ NOTHING,   40 } // Saving, intermission
};
