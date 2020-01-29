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
	{ NOTHING,  250 },
	{ TRIGGERS,   5 },
	{ NOTHING,  150 },
	{ TRIGGERS,   5 },
	{ NOTHING,  150 },
	{ A,          5 },
	{ NOTHING,  250 },

	// Talk to Pondo
	{ A,          5 }, // Start
	{ NOTHING,   30 },
	{ B,          5 }, // Quick output of text
	{ NOTHING,   20 }, // Halloo, kiddums!
	{ A,          5 }, // <- I'll try it!
	{ NOTHING,   15 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ A,          5 }, // <- OK!
	{ NOTHING,   15 },
	{ B,          5 },
	{ NOTHING,   20 }, // Aha! Play bells are ringing! I gotta set up the pins, but I'll be back in a flurry
	{ A,          5 }, // <Continue>
	{ NOTHING,  325 }, // Cut to different scene (Knock 'em flat!)
	{ B,          5 },
	{ NOTHING,   20 },
	{ A,          5 }, // <Continue> // Camera transition takes place after this
	{ NOTHING,   50 },
	{ B,          5 },
	{ NOTHING,   20 }, // If you can knock over all 10 pins in one roll, that's a strike
	{ A,          5 }, // <Continue>
	{ NOTHING,   15 },
	{ B,          5 },
	{ NOTHING,   20 }, // A spare is...
	{ A,          5 }, // <Continue>
	{ NOTHING,  100 }, // Well, good luck
	{ A,          5 }, // <Continue>
	{ NOTHING,  150 }, // Pondo walks away

	// Pick up Snowball (Or alternatively, run to bail in case of a non-strike)
	{ A,          5 },
	{ NOTHING,   50 },
	{ LEFT,      42 },
	{ UP,        80 },
	{ THROW,     25 },

	// Non-strike alternative flow, cancel bail and rethrow
	{ NOTHING,   30 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 }, // I have to split dialogue (It's nothing)
	{ NOTHING,   15 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,  450 },
	{ B,          5 }, // Snowly moly... there are rules!
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 }, // Second dialogue
	{ NOTHING,   20 },
	{ DOWN,      10 }, // Return to snowball
	{ NOTHING,   20 },
	{ A,          5 }, // Pick up snowball, we just aimlessly throw it
	{ NOTHING,   50 },
	{ UP,        10 },
	{ THROW,     25 },

	// Back at main flow
	{ NOTHING,  175 }, // Ater throw wait
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 }, // To the rewards
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	
	{ B,          5 }, // Wait for 450 cycles by bashing B (Like real players do!)
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 },
	{ B,          5 },
	{ NOTHING,   20 } // Saving, intermission
};
