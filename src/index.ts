import { BrowserWindow } from 'electron';

var native = require('bindings')('native.node')


export const makeDesktopish : (browser: BrowserWindow) => void = native.desktopish;
