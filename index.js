function getUnitStyle(u, h) {
	let s = "";
	
	s += `background-color: ${u.color_0};`;
	
	if (u.type == "text") {
		const font = u.font.split(":");
		const font_name = font[0];
		const font_size = font[1].split(",").map(x => Number.parseInt(x));
		
		s += `color: ${u.color_1};`;
		
		s += `text-align: ${u.align};`;
		s += `text-wrap: nowrap;`;
		s += `line-height: ${h + font_size[0]}px;`;
		
		s += `font-family: '${font_name}';`;
		s += `font-size: ${font_size[1]}px;`;
		s += `font-kerning: none;`;
	}
	
	if (u.type == "icon") {
		const icon = u.icon.split(":");
		const icon_name = icon[0];
		const icon_size = Number.parseInt(icon[1]);
		
		s += `color: ${u.color_1};`;
		
		s += `text-align: ${u.align};`;
		s += `text-wrap: nowrap;`;
		
		s += `font-family: 'Material Symbols Outlined';`;
		s += `font-size: ${icon_size}px;`;
	}
	
	s += `display: inline-block;`;
	s += `vertical-align: top;`;
	s += `overflow: clip;`;
	
	s += `width: ${u.w}px;`;
	s += `height: 100%;`;
	
	return s;
}

function renderUnit(u, h) {
	let r = "";
	
	r += `<div style="${getUnitStyle(u, h)}">`;
	
	if (u.type == "text") {
		r += u.text;
	}
	
	if (u.type == "icon") {
		r += u.icon.split(":")[0];
	}
	
	r += `</div>`;
	
	return r;
}

function renderObject(o) {
	let r = "";
	
	r += `<div style="width: 100%; height: ${o.h}px;">`;
	
	for (const unit of o.units) {
		r += renderUnit(unit, o.h);
	}
	
	r += `</div>`;
	
	return r;
}

function renderWindow(w) {
	let r = "";
	
	r += `<div style="background-color: ${w.color}; width: ${w.w}px; height: ${w.h}px; overflow-y: scroll;">`;
	
	for (const item of w.items) {
		r += renderObject(item);
	}
	
	r += `</div>`;
	
	return r;
}

const font_murcia_12x24 = "Terminus:0,24";
const font_lt_superior_80x160 = "LT Superior:16,132";

const icon_battery_3_28x28 = "battery_android_3:28";

const default_text = `{
	items: [
		{
			units: [
				{
					type: "none",
					color_0: "#000",
					w: 24,
				},
				
				{
					type: "text",
					color_0: "#000",
					color_1: "#F5F",
					w: 160,
					align: "left",
					text: "Alarma en 6h 58m",
					font: "Terminus:0,24",
				},
				
				{
					type: "none",
					color_0: "#000",
					w: 4,
				},
				
				{
					type: "icon",
					color_0: "#000",
					color_1: "#FFF",
					w: 28,
					align: "center",
					icon: "battery_android_3:28",
				},
				
				{
					type: "none",
					color_0: "#000",
					w: 24,
				},
			],
			
			h: 34,
			is_fixed: true,
		},
		
		{
			units: [
				{
					type: "none",
					color_0: "#F5F",
					w: 240,
				},
			],
			
			h: 2,
			is_fixed: true,
		},
		
		{
			units: [
				{
					type: "text",
					color_0: "#000",
					color_1: "#FFF",
					w: 240,
					align: "left",
					text: "12",
					font: "LT Superior:16,132",
				},
			],
			
			h: 100,
			is_fixed: false,
		},
		
		{
			units: [
				{
					type: "text",
					color_0: "#000",
					color_1: "#FFF",
					w: 240,
					align: "right",
					text: "34",
					font: "LT Superior:16,132",
				},
			],
			
			h: 100,
			is_fixed: false,
		},
		
		{
			units: [
				{
					type: "text",
					color_0: "#000",
					color_1: "#BBB",
					w: 240,
					align: "center",
					text: "18 de septiembre",
					font: "Terminus:0,24",
				},
			],
			
			h: 44,
			is_fixed: false,
		},
	],
	
	color: "#000",
	w: 240,
	h: 280,
}`;

window.onload = (function() {
	const editor = ace.edit("editor");
	
	editor.setTheme("ace/theme/textmate");
	editor.session.setMode("ace/mode/json5");
	
	editor.session.on("change", function(delta) {
		try {
			const w = JSON5.parse(editor.getValue());
			document.getElementById("target").innerHTML = renderWindow(w);
		} catch (e) {
			console.log(e);
		}
	});
	
	editor.setValue(default_text);
});
