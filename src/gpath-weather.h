#include <pebble.h>

// CLOUDY_DAY
static const int CLOUDY_DAY_PATH_COUNT = 4;
static const struct GPathInfo CLOUDY_DAY_PATHS[] = {
  { // [0] polygon 
    .num_points = 14,
    .points = (GPoint []) {
      {22, 24},
      {24, 22},
      {24, 19},
      {21, 16},
      {17, 16},
      {14, 13},
      {10, 13},
      {6, 17},
      {6, 17},
      {3, 17},
      {1, 19},
      {1, 22},
      {3, 24},
      {22, 24}
    }
  },
  { // [1] polygon 
    .num_points = 13,
    .points = (GPoint []) {
      {9, 10},
      {7, 8},
      {7, 5},
      {9, 3},
      {13, 3},
      {15, 1},
      {18, 1},
      {20, 3},
      {22, 3},
      {24, 5},
      {24, 8},
      {22, 10},
      {9, 10}
    }
  },
  { // [2] line 
    .num_points = 2,
    .points = (GPoint []) {
      {20, 3},
      {18, 5}
    }
  },
  { // [3] line 
    .num_points = 2,
    .points = (GPoint []) {
      {6, 17},
      {8, 19}
    }
  }
};

// HEAVY_RAIN
const int HEAVY_RAIN_PATH_COUNT = 5;
static const struct GPathInfo HEAVY_RAIN_PATHS[] = {
  { // [0] polygon 
    .num_points = 13,
    .points = (GPoint []) {
      {22, 12},
      {24, 10},
      {24, 7},
      {21, 4},
      {17, 4},
      {14, 1},
      {9, 1},
      {6, 4},
      {4, 4},
      {1, 7},
      {1, 10},
      {3, 12},
      {22, 12}
    }
  },
  // POLYLINE OMITTED
  { // [1] line 
    .num_points = 2,
    .points = (GPoint []) {
      {2, 23},
      {4, 15}
    }
  },
  { // [2] line 
    .num_points = 2,
    .points = (GPoint []) {
      {7, 23},
      {9, 15}
    }
  },
  { // [3] line 
    .num_points = 2,
    .points = (GPoint []) {
      {13, 19},
      {14, 15}
    }
  },
  { // [4] line 
    .num_points = 2,
    .points = (GPoint []) {
      {18, 19},
      {19, 15}
    }
  }
};

// HEAVY_SNOW
const int HEAVY_SNOW_PATH_COUNT = 8;
static const struct GPathInfo HEAVY_SNOW_PATHS[] = {
  { // [0] polygon 
    .num_points = 13,
    .points = (GPoint []) {
      {22, 12},
      {24, 10},
      {24, 6},
      {22, 4},
      {17, 4},
      {14, 1},
      {8, 1},
      {5, 4},
      {3, 4},
      {1, 6},
      {1, 10},
      {3, 12},
      {22, 12}
    }
  },
  { // [1] line 
    .num_points = 2,
    .points = (GPoint []) {
      {5, 4},
      {8, 7}
    }
  },
  { // [2] line 
    .num_points = 2,
    .points = (GPoint []) {
      {5, 19},
      {5, 15}
    }
  },
  { // [3] line 
    .num_points = 2,
    .points = (GPoint []) {
      {3, 17},
      {7, 17}
    }
  },
  { // [4] line 
    .num_points = 2,
    .points = (GPoint []) {
      {11, 24},
      {11, 20}
    }
  },
  { // [5] line 
    .num_points = 2,
    .points = (GPoint []) {
      {9, 22},
      {13, 22}
    }
  },
  { // [6] line 
    .num_points = 2,
    .points = (GPoint []) {
      {16, 19},
      {16, 15}
    }
  },
  { // [7] line 
    .num_points = 2,
    .points = (GPoint []) {
      {14, 17},
      {18, 17}
    }
  }
};

// LIGHT_RAIN
const int LIGHT_RAIN_PATH_COUNT = 6;
static const struct GPathInfo LIGHT_RAIN_PATHS[] = {
  { // [0] polygon 
    .num_points = 13,
    .points = (GPoint []) {
      {22, 12},
      {24, 10},
      {24, 6},
      {22, 4},
      {17, 4},
      {14, 1},
      {8, 1},
      {5, 4},
      {3, 4},
      {1, 6},
      {1, 10},
      {3, 12},
      {22, 12}
    }
  },
  { // [1] line 
    .num_points = 2,
    .points = (GPoint []) {
      {5, 4},
      {8, 7}
    }
  },
  { // [2] line 
    .num_points = 2,
    .points = (GPoint []) {
      {14, 18},
      {14, 15}
    }
  },
  { // [3] line 
    .num_points = 2,
    .points = (GPoint []) {
      {4, 18},
      {4, 15}
    }
  },
  { // [4] line 
    .num_points = 2,
    .points = (GPoint []) {
      {9, 21},
      {9, 18}
    }
  },
  { // [5] line 
    .num_points = 2,
    .points = (GPoint []) {
      {4, 24},
      {4, 21}
    }
  }
};

// LIGHT_SNOW
const int LIGHT_SNOW_PATH_COUNT = 6;
static const struct GPathInfo LIGHT_SNOW_PATHS[] = {
  { // [0] polygon 
    .num_points = 13,
    .points = (GPoint []) {
      {22, 12},
      {24, 10},
      {24, 6},
      {22, 4},
      {17, 4},
      {14, 1},
      {8, 1},
      {5, 4},
      {3, 4},
      {1, 6},
      {1, 10},
      {3, 12},
      {22, 12}
    }
  },
  { // [1] line 
    .num_points = 2,
    .points = (GPoint []) {
      {5, 4},
      {8, 7}
    }
  },
  { // [2] line 
    .num_points = 2,
    .points = (GPoint []) {
      {5, 19},
      {5, 15}
    }
  },
  { // [3] line 
    .num_points = 2,
    .points = (GPoint []) {
      {3, 17},
      {7, 17}
    }
  },
  { // [4] line 
    .num_points = 2,
    .points = (GPoint []) {
      {11, 24},
      {11, 20}
    }
  },
  { // [5] line 
    .num_points = 2,
    .points = (GPoint []) {
      {9, 22},
      {13, 22}
    }
  }
};

// PARTLY_CLOUDY
const int PARTLY_CLOUDY_PATH_COUNT = 7;
static const struct GPathInfo PARTLY_CLOUDY_PATHS[] = {
  { // [0] polygon 
    .num_points = 9,
    .points = (GPoint []) {
      {13, 4},
      {11, 6},
      {11, 9},
      {13, 11},
      {16, 11},
      {18, 9},
      {18, 6},
      {16, 4},
      {13, 4}
    }
  },
  { // [1] line 
    .num_points = 2,
    .points = (GPoint []) {
      {7, 1},
      {9, 3}
    }
  },
  { // [2] line 
    .num_points = 2,
    .points = (GPoint []) {
      {22, 1},
      {20, 3}
    }
  },
  { // [3] polygon 
    .num_points = 13,
    .points = (GPoint []) {
      {22, 24},
      {24, 22},
      {24, 18},
      {22, 16},
      {16, 16},
      {13, 13},
      {9, 13},
      {6, 16},
      {3, 16},
      {1, 18},
      {1, 22},
      {3, 24},
      {22, 24}
    }
  },
  { // [4] line 
    .num_points = 2,
    .points = (GPoint []) {
      {6, 16},
      {9, 19}
    }
  },
  { // [5] line 
    .num_points = 2,
    .points = (GPoint []) {
      {21, 8},
      {24, 8}
    }
  },
  { // [6] line 
    .num_points = 2,
    .points = (GPoint []) {
      {5, 8},
      {8, 8}
    }
  }
};

// RAINING_AND_SNOWING
const int RAINING_AND_SNOWING_PATH_COUNT = 6;
static const struct GPathInfo RAINING_AND_SNOWING_PATHS[] = {
  { // [0] polygon 
    .num_points = 13,
    .points = (GPoint []) {
      {22, 12},
      {24, 10},
      {24, 6},
      {22, 4},
      {17, 4},
      {14, 1},
      {8, 1},
      {5, 4},
      {3, 4},
      {1, 6},
      {1, 10},
      {3, 12},
      {22, 12}
    }
  },
  { // [1] line 
    .num_points = 2,
    .points = (GPoint []) {
      {5, 4},
      {8, 7}
    }
  },
  { // [2] line 
    .num_points = 2,
    .points = (GPoint []) {
      {5, 19},
      {5, 15}
    }
  },
  { // [3] line 
    .num_points = 2,
    .points = (GPoint []) {
      {11, 24},
      {11, 20}
    }
  },
  { // [4] line 
    .num_points = 2,
    .points = (GPoint []) {
      {16, 19},
      {16, 15}
    }
  },
  { // [5] line 
    .num_points = 2,
    .points = (GPoint []) {
      {14, 17},
      {18, 17}
    }
  }
};

// TIMELINE_SUN
const int TIMELINE_SUN_PATH_COUNT = 9;
static const struct GPathInfo TIMELINE_SUN_PATHS[] = {
  { // [0] polygon 
    .num_points = 9,
    .points = (GPoint []) {
      {10, 6},
      {6, 10},
      {6, 14},
      {10, 18},
      {14, 18},
      {18, 14},
      {18, 10},
      {14, 6},
      {10, 6}
    }
  },
  { // [1] line 
    .num_points = 2,
    .points = (GPoint []) {
      {12, 1},
      {12, 3}
    }
  },
  { // [2] line 
    .num_points = 2,
    .points = (GPoint []) {
      {12, 24},
      {12, 21}
    }
  },
  { // [3] line 
    .num_points = 2,
    .points = (GPoint []) {
      {1, 23},
      {5, 19}
    }
  },
  { // [4] line 
    .num_points = 2,
    .points = (GPoint []) {
      {3, 3},
      {5, 5}
    }
  },
  { // [5] line 
    .num_points = 2,
    .points = (GPoint []) {
      {23, 23},
      {19, 19}
    }
  },
  { // [6] line 
    .num_points = 2,
    .points = (GPoint []) {
      {21, 3},
      {19, 5}
    }
  },
  { // [7] line 
    .num_points = 2,
    .points = (GPoint []) {
      {3, 12},
      {1, 12}
    }
  },
  { // [8] line 
    .num_points = 2,
    .points = (GPoint []) {
      {23, 12},
      {21, 12}
    }
  }
};

// TIMELINE_WEATHER
const int TIMELINE_WEATHER_PATH_COUNT = 8;
static const struct GPathInfo TIMELINE_WEATHER_PATHS[] = {
  { // [0] polygon 
    .num_points = 9,
    .points = (GPoint []) {
      {18, 6},
      {16, 8},
      {16, 12},
      {18, 14},
      {22, 14},
      {24, 12},
      {24, 8},
      {22, 6},
      {18, 6}
    }
  },
  { // [1] line 
    .num_points = 2,
    .points = (GPoint []) {
      {20, 1},
      {20, 3}
    }
  },
  { // [2] line 
    .num_points = 2,
    .points = (GPoint []) {
      {13, 3},
      {15, 5}
    }
  },
  { // [3] polygon 
    .num_points = 13,
    .points = (GPoint []) {
      {22, 20},
      {24, 18},
      {24, 14},
      {22, 12},
      {15, 12},
      {12, 9},
      {9, 9},
      {6, 12},
      {3, 12},
      {1, 14},
      {1, 18},
      {3, 20},
      {22, 20}
    }
  },
  { // [4] line 
    .num_points = 2,
    .points = (GPoint []) {
      {6, 12},
      {8, 14}
    }
  },
  { // [5] line 
    .num_points = 2,
    .points = (GPoint []) {
      {4, 24},
      {4, 23}
    }
  },
  { // [6] line 
    .num_points = 2,
    .points = (GPoint []) {
      {8, 24},
      {8, 23}
    }
  },
  { // [7] line 
    .num_points = 2,
    .points = (GPoint []) {
      {12, 24},
      {12, 23}
    }
  }
};








