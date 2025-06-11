const programName = "BlockBreakJS"

const renderWidth = 640;
const renderHeight = 472;

const fontHeight = 16;

const playerSpeed = Math.round(renderWidth / 80);
const playerWidth = Math.round(renderWidth / 40);
const playerHeight = Math.round(renderWidth / 40);
const playerStartX = Math.round((renderWidth / 2) - (playerWidth / 2));
const playerStartY = renderHeight - (playerHeight * 3);
     
const screenEdgeUp = 0;
const screenEdgeDown = renderHeight - playerHeight;
const screenEdgeLeft = 0;
const screenEdgeRight = renderWidth - playerWidth;

const touchDeadZone = 32;

const maxBlocks = 255;
const maxFPS = 30;