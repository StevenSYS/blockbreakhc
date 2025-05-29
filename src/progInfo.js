program_name = "BlockBreakJS"

screen_width = 640;
screen_height = 472;

font_height = 16;

player_speed = Math.round(screen_width / 80);
player_width = Math.round(screen_width / 40);
player_height = Math.round(screen_width / 40);
player_startX = Math.round((screen_width / 2) - (player_width / 2));
player_startY = screen_height - (player_height * 3);

screen_edgeUp = 0;
screen_edgeDown = screen_height - player_height;
screen_edgeLeft = 0;
screen_edgeRight = screen_width - player_width;

max_blocks = 255;
max_fps = 30;
max_ms = 1000 / max_fps;