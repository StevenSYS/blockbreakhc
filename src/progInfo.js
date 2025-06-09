const program_name = "BlockBreakJS"

const render_width = 640;
const render_height = 472;

const font_height = 16;

const player_speed = Math.round(render_width / 80);
const player_width = Math.round(render_width / 40);
const player_height = Math.round(render_width / 40);
const player_startX = Math.round((render_width / 2) - (player_width / 2));
const player_startY = render_height - (player_height * 3);
     
const screen_edgeUp = 0;
const screen_edgeDown = render_height - player_height;
const screen_edgeLeft = 0;
const screen_edgeRight = render_width - player_width;

const touch_threshold = 64;

const max_blocks = 255;
const max_fps = 30;
const max_ms = 1000 / max_fps;