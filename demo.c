#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <span.h>

#include "font/font.h"
#include "icon/icon.h"

static SDL_Window *sdl2_window;
static SDL_Renderer *sdl2_renderer;

static int sdl2_x, sdl2_y;

void sdl2_span(int n, uint16_t color) {
	const int r = (((color >> 8) & 15) * 255) / 15;
	const int g = (((color >> 4) & 15) * 255) / 15;
	const int b = (((color >> 0) & 15) * 255) / 15;
	
	SDL_SetRenderDrawColor(sdl2_renderer, r, g, b, 255);
	
	for (int i = 0; i < n; i++) {
		SDL_RenderDrawPoint(sdl2_renderer, sdl2_x++, sdl2_y);
	}
}

void sdl2_copy(int n, const uint16_t *array) {
	for (int i = 0; i < n; i++) {
		const int r = (((array[i] >> 8) & 15) * 255) / 15;
		const int g = (((array[i] >> 4) & 15) * 255) / 15;
		const int b = (((array[i] >> 0) & 15) * 255) / 15;
		
		SDL_SetRenderDrawColor(sdl2_renderer, r, g, b, 255);
		SDL_RenderDrawPoint(sdl2_renderer, sdl2_x++, sdl2_y);
	}
}

void sdl2_mask(int n, const uint16_t *array, uint16_t color_0, uint16_t color_1) {
	const int r_0 = (((color_0 >> 8) & 15) * 255) / 15;
	const int g_0 = (((color_0 >> 4) & 15) * 255) / 15;
	const int b_0 = (((color_0 >> 0) & 15) * 255) / 15;
	
	const int r_1 = (((color_1 >> 8) & 15) * 255) / 15;
	const int g_1 = (((color_1 >> 4) & 15) * 255) / 15;
	const int b_1 = (((color_1 >> 0) & 15) * 255) / 15;
	
	for (int i = 0; i < n; i++) {
		if (((array[i >> 4] >> (i & 15)) & 1) > 0) {
			SDL_SetRenderDrawColor(sdl2_renderer, r_1, g_1, b_1, 255);
		} else {
			SDL_SetRenderDrawColor(sdl2_renderer, r_0, g_0, b_0, 255);
		}
		
		SDL_RenderDrawPoint(sdl2_renderer, sdl2_x++, sdl2_y);
	}
}

const span_pipe_t sdl2_pipe = (const span_pipe_t) {
	.span = sdl2_span,
	.copy = sdl2_copy,
	.mask = sdl2_mask,
};

void menu_on_enter(const span_window_t *window, int i) {
	span_edit_color_1(window, i, 0xFFFF);
	
	if (i == 6) {
		span_edit_color_0(window, i, 0xF727);
	}
	
	if (i == 7) {
		span_edit_color_0(window, i, 0xF277);
	}
	
	if (i == 8) {
		span_edit_color_0(window, i, 0xF751);
	}
	
	if (i == 9) {
		span_edit_color_0(window, i, 0xF272);
	}
	
	if (i == 10) {
		span_edit_color_0(window, i, 0xF257);
	}
	
	if (i == 11) {
		span_edit_color_0(window, i, 0xF771);
	}
	
	if (i == 12) {
		span_edit_color_0(window, i, 0xF722);
	}
	
	if (i == 13) {
		span_edit_color_0(window, i, 0xF437);
	}
	
	if (i == 14) {
		span_edit_color_0(window, i, 0xF666);
	}
	
	if (i == 15) {
		span_edit_color_0(window, i, 0xF666);
	}
}

void menu_on_leave(const span_window_t *window, int i) {
	span_edit_color_0(window, i, 0xF000);
	
	if (i == 6) {
		span_edit_color_1(window, i, 0xFF5F);
	}
	
	if (i == 7) {
		span_edit_color_1(window, i, 0xF5FF);
	}
	
	if (i == 8) {
		span_edit_color_1(window, i, 0xFFB3);
	}
	
	if (i == 9) {
		span_edit_color_1(window, i, 0xF5F5);
	}
	
	if (i == 10) {
		span_edit_color_1(window, i, 0xF5BF);
	}
	
	if (i == 11) {
		span_edit_color_1(window, i, 0xFFF3);
	}
	
	if (i == 12) {
		span_edit_color_1(window, i, 0xFF55);
	}
	
	if (i == 13) {
		span_edit_color_1(window, i, 0xF97F);
	}
	
	if (i == 14) {
		span_edit_color_1(window, i, 0xFDDD);
	}
	
	if (i == 15) {
		span_edit_color_1(window, i, 0xFDDD);
	}
}

int main(void) {
	SDL_Init(SDL_INIT_VIDEO);
	
	sdl2_window = SDL_CreateWindow("span", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 240, 280, 0);
	sdl2_renderer = SDL_CreateRenderer(sdl2_window, -1, SDL_RENDERER_ACCELERATED);
	
	span_init(sdl2_pipe);
	
	span_unit_t icon_units[] = {
		(span_unit_t) {
			.type = SPAN_UNIT_NONE,
			.color_0 = 0xF000,
			.w = 24,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_TEXT,
			.color_0 = 0xF000,
			.color_1 = 0xFF5F,
			.w = 160,
			.align = SPAN_ALIGN_LEFT,
			.text = "Alarma en 6h 58m",
			.font = &font_terminus_12x24,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_NONE,
			.color_0 = 0xF000,
			.w = 4,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_ICON,
			.color_0 = 0xF000,
			.color_1 = 0xFFFF,
			.w = 28,
			.align = SPAN_ALIGN_CENTER,
			.icon = &icon_battery_3_28x28,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_NONE,
			.color_0 = 0xF000,
			.w = 24,
		},
	};
	
	span_unit_t icon_border_units[] = {
		(span_unit_t) {
			.type = SPAN_UNIT_NONE,
			.color_0 = 0xFF5F,
			.w = 240,
		},
	};
	
	span_unit_t hour_units[] = {
		(span_unit_t) {
			.type = SPAN_UNIT_TEXT,
			.color_0 = 0xF000,
			.color_1 = 0xFFFF,
			.w = 240,
			.align = SPAN_ALIGN_LEFT,
			.text = "12",
			.font = &font_lt_superior_80x160,
		},
	};
	
	span_unit_t minute_units[] = {
		(span_unit_t) {
			.type = SPAN_UNIT_TEXT,
			.color_0 = 0xF000,
			.color_1 = 0xFFFF,
			.w = 240,
			.align = SPAN_ALIGN_RIGHT,
			.text = "34",
			.font = &font_lt_superior_80x160,
		},
	};
	
	span_unit_t date_units[] = {
		(span_unit_t) {
			.type = SPAN_UNIT_TEXT,
			.color_0 = 0xF000,
			.color_1 = 0xFBBB,
			.w = 240,
			.align = SPAN_ALIGN_CENTER,
			.text = "18 de septiembre",
			.font = &font_terminus_12x24,
		},
	};
	
	span_unit_t filler_units[] = {
		(span_unit_t) {
			.type = SPAN_UNIT_NONE,
			.color_0 = SPAN_COLOR(0, 0, 0),
			.w = 240,
		},
	};
	
	span_unit_t menu_0_units[] = {
		(span_unit_t) {
			.type = SPAN_UNIT_ICON,
			.color_0 = 0xF000,
			.color_1 = 0xFF5F,
			.w = 44,
			.align = SPAN_ALIGN_CENTER,
			.icon = &icon_alarm_40x40,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_NONE,
			.color_0 = 0xF000,
			.w = 4,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_TEXT,
			.color_0 = 0xF000,
			.color_1 = 0xFF5F,
			.w = 192,
			.align = SPAN_ALIGN_LEFT,
			.text = "Alarmas",
			.font = &font_terminus_12x24,
		},
	};
	
	span_unit_t menu_1_units[] = {
		(span_unit_t) {
			.type = SPAN_UNIT_ICON,
			.color_0 = 0xF000,
			.color_1 = 0xF5FF,
			.w = 44,
			.align = SPAN_ALIGN_CENTER,
			.icon = &icon_alarm_40x40,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_NONE,
			.color_0 = 0xF000,
			.w = 4,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_TEXT,
			.color_0 = 0xF000,
			.color_1 = 0xF5FF,
			.w = 192,
			.align = SPAN_ALIGN_LEFT,
			.text = "Cron\xA2metro",
			.font = &font_terminus_12x24,
		},
	};
	
	span_unit_t menu_2_units[] = {
		(span_unit_t) {
			.type = SPAN_UNIT_ICON,
			.color_0 = 0xF000,
			.color_1 = 0xFFB3,
			.w = 44,
			.align = SPAN_ALIGN_CENTER,
			.icon = &icon_alarm_40x40,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_NONE,
			.color_0 = 0xF000,
			.w = 4,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_TEXT,
			.color_0 = 0xF000,
			.color_1 = 0xFFB3,
			.w = 192,
			.align = SPAN_ALIGN_LEFT,
			.text = "Temporizador",
			.font = &font_terminus_12x24,
		},
	};
	
	span_unit_t menu_3_units[] = {
		(span_unit_t) {
			.type = SPAN_UNIT_ICON,
			.color_0 = 0xF000,
			.color_1 = 0xF5F5,
			.w = 44,
			.align = SPAN_ALIGN_CENTER,
			.icon = &icon_alarm_40x40,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_NONE,
			.color_0 = 0xF000,
			.w = 4,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_TEXT,
			.color_0 = 0xF000,
			.color_1 = 0xF5F5,
			.w = 192,
			.align = SPAN_ALIGN_LEFT,
			.text = "Pulsos (BPM)",
			.font = &font_terminus_12x24,
		},
	};
	
	span_unit_t menu_4_units[] = {
		(span_unit_t) {
			.type = SPAN_UNIT_ICON,
			.color_0 = 0xF000,
			.color_1 = 0xF5BF,
			.w = 44,
			.align = SPAN_ALIGN_CENTER,
			.icon = &icon_alarm_40x40,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_NONE,
			.color_0 = 0xF000,
			.w = 4,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_TEXT,
			.color_0 = 0xF000,
			.color_1 = 0xF5BF,
			.w = 192,
			.align = SPAN_ALIGN_LEFT,
			.text = "Calendario",
			.font = &font_terminus_12x24,
		},
	};
	
	span_unit_t menu_5_units[] = {
		(span_unit_t) {
			.type = SPAN_UNIT_ICON,
			.color_0 = 0xF000,
			.color_1 = 0xFFF3,
			.w = 44,
			.align = SPAN_ALIGN_CENTER,
			.icon = &icon_alarm_40x40,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_NONE,
			.color_0 = 0xF000,
			.w = 4,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_TEXT,
			.color_0 = 0xF000,
			.color_1 = 0xFFF3,
			.w = 192,
			.align = SPAN_ALIGN_LEFT,
			.text = "Linterna",
			.font = &font_terminus_12x24,
		},
	};
	
	span_unit_t menu_6_units[] = {
		(span_unit_t) {
			.type = SPAN_UNIT_ICON,
			.color_0 = 0xF000,
			.color_1 = 0xFF55,
			.w = 44,
			.align = SPAN_ALIGN_CENTER,
			.icon = &icon_alarm_40x40,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_NONE,
			.color_0 = 0xF000,
			.w = 4,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_TEXT,
			.color_0 = 0xF000,
			.color_1 = 0xFF55,
			.w = 192,
			.align = SPAN_ALIGN_LEFT,
			.text = "Afinador",
			.font = &font_terminus_12x24,
		},
	};
	
	span_unit_t menu_7_units[] = {
		(span_unit_t) {
			.type = SPAN_UNIT_ICON,
			.color_0 = 0xF000,
			.color_1 = 0xF97F,
			.w = 44,
			.align = SPAN_ALIGN_CENTER,
			.icon = &icon_alarm_40x40,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_NONE,
			.color_0 = 0xF000,
			.w = 4,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_TEXT,
			.color_0 = 0xF000,
			.color_1 = 0xF97F,
			.w = 192,
			.align = SPAN_ALIGN_LEFT,
			.text = "Guitarra",
			.font = &font_terminus_12x24,
		},
	};
	
	span_unit_t menu_8_units[] = {
		(span_unit_t) {
			.type = SPAN_UNIT_ICON,
			.color_0 = 0xF000,
			.color_1 = 0xFDDD,
			.w = 44,
			.align = SPAN_ALIGN_CENTER,
			.icon = &icon_alarm_40x40,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_NONE,
			.color_0 = 0xF000,
			.w = 4,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_TEXT,
			.color_0 = 0xF000,
			.color_1 = 0xFDDD,
			.w = 192,
			.align = SPAN_ALIGN_LEFT,
			.text = "Transferir",
			.font = &font_terminus_12x24,
		},
	};
	
	span_unit_t menu_9_units[] = {
		(span_unit_t) {
			.type = SPAN_UNIT_ICON,
			.color_0 = 0xF000,
			.color_1 = 0xFDDD,
			.w = 44,
			.align = SPAN_ALIGN_CENTER,
			.icon = &icon_alarm_40x40,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_NONE,
			.color_0 = 0xF000,
			.w = 4,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_TEXT,
			.color_0 = 0xF000,
			.color_1 = 0xFDDD,
			.w = 192,
			.align = SPAN_ALIGN_LEFT,
			.text = "Configurar",
			.font = &font_terminus_12x24,
		},
	};
	
	span_unit_t text_scroll_1_units[] = {
		(span_unit_t) {
			.type = SPAN_UNIT_NONE,
			.color_0 = SPAN_COLOR(0, 0, 0),
			.w = 4,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_TEXT,
			.color_0 = SPAN_COLOR(0, 0, 0),
			.color_1 = SPAN_COLOR(0, 15, 15),
			.w = 232,
			.align = SPAN_ALIGN_CENTER,
			.text = "Hey! Don't mind me, I'm just testing scrolling <3.",
			.font = &font_terminus_12x24,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_NONE,
			.color_0 = SPAN_COLOR(0, 0, 0),
			.w = 4,
		},
	};
	
	span_unit_t text_scroll_2_units[] = {
		(span_unit_t) {
			.type = SPAN_UNIT_NONE,
			.color_0 = SPAN_COLOR(0, 0, 0),
			.w = 4,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_TEXT,
			.color_0 = SPAN_COLOR(0, 0, 0),
			.color_1 = SPAN_COLOR(15, 15, 0),
			.w = 232,
			.align = SPAN_ALIGN_CENTER,
			.text = "Now I'm just testing different lengths!",
			.font = &font_terminus_12x24,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_NONE,
			.color_0 = SPAN_COLOR(0, 0, 0),
			.w = 4,
		},
	};
	
	span_unit_t text_scroll_3_units[] = {
		(span_unit_t) {
			.type = SPAN_UNIT_NONE,
			.color_0 = SPAN_COLOR(0, 0, 0),
			.w = 4,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_TEXT,
			.color_0 = SPAN_COLOR(0, 0, 0),
			.color_1 = SPAN_COLOR(15, 0, 15),
			.w = 232,
			.align = SPAN_ALIGN_CENTER,
			.text = "And this one is meant to be incredibly huge and to scroll quite far.",
			.font = &font_terminus_12x24,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_NONE,
			.color_0 = SPAN_COLOR(0, 0, 0),
			.w = 4,
		},
	};
	
	span_unit_t text_scroll_4_units[] = {
		(span_unit_t) {
			.type = SPAN_UNIT_NONE,
			.color_0 = SPAN_COLOR(0, 0, 0),
			.w = 4,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_TEXT,
			.color_0 = SPAN_COLOR(0, 0, 0),
			.color_1 = SPAN_COLOR(15, 15, 15),
			.w = 232,
			.align = SPAN_ALIGN_CENTER,
			.text = "This barely scrolls.",
			.font = &font_terminus_12x24,
		},
		(span_unit_t) {
			.type = SPAN_UNIT_NONE,
			.color_0 = SPAN_COLOR(0, 0, 0),
			.w = 4,
		},
	};
	
	span_object_t root_items[] = {
		(span_object_t) {
			.units = icon_units,
			.n = sizeof(icon_units) / sizeof(span_unit_t),
			.h = 34,
			.is_hoverable = true,
			.is_fixed = true,
			.on_enter = NULL,
			.on_leave = NULL,
			.on_press = NULL,
		},
		(span_object_t) {
			.units = icon_border_units,
			.n = sizeof(icon_units) / sizeof(span_unit_t),
			.h = 2,
			.is_hoverable = false,
			.is_fixed = true,
			.on_enter = NULL,
			.on_leave = NULL,
			.on_press = NULL,
		},
		(span_object_t) {
			.units = hour_units,
			.n = sizeof(hour_units) / sizeof(span_unit_t),
			.h = 100,
			.is_hoverable = false,
			.is_fixed = false,
			.on_enter = NULL,
			.on_leave = NULL,
			.on_press = NULL,
		},
		(span_object_t) {
			.units = minute_units,
			.n = sizeof(minute_units) / sizeof(span_unit_t),
			.h = 100,
			.is_hoverable = false,
			.is_fixed = false,
			.on_enter = NULL,
			.on_leave = NULL,
			.on_press = NULL,
		},
		(span_object_t) {
			.units = date_units,
			.n = sizeof(date_units) / sizeof(span_unit_t),
			.h = 44,
			.is_hoverable = false,
			.is_fixed = false,
			.on_enter = NULL,
			.on_leave = NULL,
			.on_press = NULL,
		},
		(span_object_t) {
			.units = filler_units,
			.n = sizeof(filler_units) / sizeof(span_unit_t),
			.h = (280 - 44) / 2,
			.is_hoverable = false,
			.is_fixed = false,
			.on_enter = NULL,
			.on_leave = NULL,
			.on_press = NULL,
		},
		(span_object_t) {
			.units = menu_0_units,
			.n = sizeof(menu_0_units) / sizeof(span_unit_t),
			.h = 44,
			.is_hoverable = true,
			.is_fixed = false,
			.on_enter = menu_on_enter,
			.on_leave = menu_on_leave,
			.on_press = NULL,
		},
		(span_object_t) {
			.units = menu_1_units,
			.n = sizeof(menu_1_units) / sizeof(span_unit_t),
			.h = 44,
			.is_hoverable = true,
			.is_fixed = false,
			.on_enter = menu_on_enter,
			.on_leave = menu_on_leave,
			.on_press = NULL,
		},
		(span_object_t) {
			.units = menu_2_units,
			.n = sizeof(menu_2_units) / sizeof(span_unit_t),
			.h = 44,
			.is_hoverable = true,
			.is_fixed = false,
			.on_enter = menu_on_enter,
			.on_leave = menu_on_leave,
			.on_press = NULL,
		},
		(span_object_t) {
			.units = menu_3_units,
			.n = sizeof(menu_3_units) / sizeof(span_unit_t),
			.h = 44,
			.is_hoverable = true,
			.is_fixed = false,
			.on_enter = menu_on_enter,
			.on_leave = menu_on_leave,
			.on_press = NULL,
		},
		(span_object_t) {
			.units = menu_4_units,
			.n = sizeof(menu_4_units) / sizeof(span_unit_t),
			.h = 44,
			.is_hoverable = true,
			.is_fixed = false,
			.on_enter = menu_on_enter,
			.on_leave = menu_on_leave,
			.on_press = NULL,
		},
		(span_object_t) {
			.units = menu_5_units,
			.n = sizeof(menu_5_units) / sizeof(span_unit_t),
			.h = 44,
			.is_hoverable = true,
			.is_fixed = false,
			.on_enter = menu_on_enter,
			.on_leave = menu_on_leave,
			.on_press = NULL,
		},
		(span_object_t) {
			.units = menu_6_units,
			.n = sizeof(menu_6_units) / sizeof(span_unit_t),
			.h = 44,
			.is_hoverable = true,
			.is_fixed = false,
			.on_enter = menu_on_enter,
			.on_leave = menu_on_leave,
			.on_press = NULL,
		},
		(span_object_t) {
			.units = menu_7_units,
			.n = sizeof(menu_7_units) / sizeof(span_unit_t),
			.h = 44,
			.is_hoverable = true,
			.is_fixed = false,
			.on_enter = menu_on_enter,
			.on_leave = menu_on_leave,
			.on_press = NULL,
		},
		(span_object_t) {
			.units = menu_8_units,
			.n = sizeof(menu_8_units) / sizeof(span_unit_t),
			.h = 44,
			.is_hoverable = true,
			.is_fixed = false,
			.on_enter = menu_on_enter,
			.on_leave = menu_on_leave,
			.on_press = NULL,
		},
		(span_object_t) {
			.units = menu_9_units,
			.n = sizeof(menu_9_units) / sizeof(span_unit_t),
			.h = 44,
			.is_hoverable = true,
			.is_fixed = false,
			.on_enter = menu_on_enter,
			.on_leave = menu_on_leave,
			.on_press = NULL,
		},
		(span_object_t) {
			.units = text_scroll_1_units,
			.n = sizeof(text_scroll_1_units) / sizeof(span_unit_t),
			.h = 28,
			.is_hoverable = true,
			.is_fixed = false,
			.on_enter = NULL,
			.on_leave = NULL,
			.on_press = NULL,
		},
		(span_object_t) {
			.units = text_scroll_2_units,
			.n = sizeof(text_scroll_2_units) / sizeof(span_unit_t),
			.h = 28,
			.is_hoverable = true,
			.is_fixed = false,
			.on_enter = NULL,
			.on_leave = NULL,
			.on_press = NULL,
		},
		(span_object_t) {
			.units = text_scroll_3_units,
			.n = sizeof(text_scroll_3_units) / sizeof(span_unit_t),
			.h = 28,
			.is_hoverable = true,
			.is_fixed = false,
			.on_enter = NULL,
			.on_leave = NULL,
			.on_press = NULL,
		},
		(span_object_t) {
			.units = text_scroll_4_units,
			.n = sizeof(text_scroll_4_units) / sizeof(span_unit_t),
			.h = 28,
			.is_hoverable = true,
			.is_fixed = false,
			.on_enter = NULL,
			.on_leave = NULL,
			.on_press = NULL,
		},
	};
	
	span_window_t root = (span_window_t) {
		.items = root_items,
		.n = sizeof(root_items) / sizeof(span_object_t),
		.color = SPAN_COLOR(0, 0, 0),
		.w = 240,
		.line = 0,
		.i = 0,
	};
	
	bool keep_running = true;
	SDL_Event event;
	
	while (keep_running) {
		span_update(SDL_GetTicks());
		
		SDL_SetRenderDrawColor(sdl2_renderer, 0, 0, 0, 255);
    	SDL_RenderClear(sdl2_renderer);
		
		for (int i = 0; i < 280; i++) {
			sdl2_x = 0;
			sdl2_y = i;
			
			span_draw_window(&root, i);
		}
		
		SDL_SetRenderDrawColor(sdl2_renderer, 211, 211, 211, 255);
		
		for (int i = 0; i < 47; i++) {
			for (int j = 0; j < 47; j++) {
				if (i * i + j * j < 47 * 47) {
					continue;
				}
				
				SDL_RenderDrawPoint(sdl2_renderer, 46 - j, 46 - i);
				SDL_RenderDrawPoint(sdl2_renderer, 239 - (46 - j), 46 - i);
			}
		}
		
		for (int i = 0; i < 43; i++) {
			for (int j = 0; j < 43; j++) {
				if (i * i + j * j < 43 * 43) {
					continue;
				}
				
				SDL_RenderDrawPoint(sdl2_renderer, 42 - j, 279 - (42 - i));
				SDL_RenderDrawPoint(sdl2_renderer, 239 - (42 - j), 279 - (42 - i));
			}
		}
		
		SDL_RenderPresent(sdl2_renderer);
		
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				keep_running = false;
				break;
			}
			
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_z) {
					span_last(&root);
					
					const int offset = (root.i ? (span_midway(&root, root.i) - 140) : 0);
					span_lerp(&root.line, root.line, offset, 500, span_poly_3);
				}
				
				if (event.key.keysym.sym == SDLK_x) {
					span_press(&root);
				}
				
				if (event.key.keysym.sym == SDLK_c) {
					span_next(&root);
					
					const int offset = (root.i ? (span_midway(&root, root.i) - 140) : 0);
					span_lerp(&root.line, root.line, offset, 500, span_poly_3);
				}
			}
		}
	}
	
	return 0;
}