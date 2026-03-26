const char *keycode_to_str(int code) {
    switch (code) {
        case 1:   return "ESC";
        case 2:   return "1";
        case 3:   return "2";
        case 4:   return "3";
        case 5:   return "4";
        case 6:   return "5";
        case 7:   return "6";
        case 8:   return "7";
        case 9:   return "8";
        case 10:  return "9";
        case 11:  return "0";
        case 12:  return "-";
        case 13:  return "=";
        case 14:  return "[BACKSPACE]";
        case 15:  return "[TAB]";
        case 16:  return "q";
        case 17:  return "w";
        case 18:  return "e";
        case 19:  return "r";
        case 20:  return "t";
        case 21:  return "y";
        case 22:  return "u";
        case 23:  return "i";
        case 24:  return "o";
        case 25:  return "p";
        case 26:  return "[";
        case 27:  return "]";
        case 28:  return "[ENTER]";
        case 29:  return "[CTRL]";
        case 30:  return "a";
        case 31:  return "s";
        case 32:  return "d";
        case 33:  return "f";
        case 34:  return "g";
        case 35:  return "h";
        case 36:  return "j";
        case 37:  return "k";
        case 38:  return "l";
        case 39:  return ";";
        case 40:  return "'";
        case 41:  return "`";
        case 42:  return "[LSHIFT]";
        case 43:  return "\\";
        case 44:  return "z";
        case 45:  return "x";
        case 46:  return "c";
        case 47:  return "v";
        case 48:  return "b";
        case 49:  return "n";
        case 50:  return "m";
        case 51:  return ",";
        case 52:  return ".";
        case 53:  return "/";
        case 54:  return "[RSHIFT]";
        case 55: return "*";   // numpad *
        case 56:  return "[ALT]";
        case 57:  return "[SPACE]";
        case 58:  return "[CAPSLOCK]";
        case 74: return "-";   // numpad 
        case 78: return "+";   // numpad +
        case 96: return "[ENTER]";  // numpad enter
        case 98: return "/";   // numpad /
        case 103: return "[UP]";
        case 105: return "[LEFT]";
        case 106: return "[RIGHT]";
        case 108: return "[DOWN]";
        case 111: return "[DELETE]";
        default:  return "[UNKNOWN]";
    }
}


const char *keycode_to_str_shifted(int code) {
    switch (code) {
        case 2:  return "!";
        case 3:  return "@";
        case 4:  return "#";
        case 5:  return "$";
        case 6:  return "%";
        case 7:  return "^";
        case 8:  return "&";
        case 9:  return "*";
        case 10: return "(";
        case 11: return ")";
        case 12: return "_";
        case 13: return "+";
        case 16: return "Q";
        case 17: return "W";
        case 18: return "E";
        case 19: return "R";
        case 20: return "T";
        case 21: return "Y";
        case 22: return "U";
        case 23: return "I";
        case 24: return "O";
        case 25: return "P";
        case 26: return "{";   // [ shifted
        case 27: return "}";   // ] shifted
        case 30: return "A";
        case 31: return "S";
        case 32: return "D";
        case 33: return "F";
        case 34: return "G";
        case 35: return "H";
        case 36: return "J";
        case 37: return "K";
        case 38: return "L";
        case 39: return ":";
        case 40: return "\"";
        case 43: return "|";   // \ shifted
        case 45: return "X";
        case 46: return "C";
        case 47: return "V";
        case 48: return "B";
        case 49: return "N";
        case 50: return "M";
        case 51: return "<";
        case 52: return ">";
        case 53: return "?";
        // anything without a shifted variant falls back to normal
        default: return keycode_to_str(code);
    }
}
