Flat profile:

Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  ms/call  ms/call  name    
 65.44      4.69     4.69   288000     0.02     0.02  draw_floor_and_ceil
 11.02      5.48     0.79 186117010     0.00     0.00  game_draw_pixel
  8.09      6.06     0.58      360     1.61     1.61  hud_put
  4.74      6.40     0.34      360     0.94     0.98  game_draw_sprites
  4.60      6.73     0.33      360     0.92     0.92  hud_fill
  3.91      7.01     0.28      360     0.78    16.86  game_render
  1.12      7.09     0.08      360     0.22     1.83  game_draw_all
  0.70      7.14     0.05   637200     0.00     0.00  game_draw_rect
  0.28      7.16     0.02      360     0.06     0.31  map_draw
  0.14      7.17     0.01   288000     0.00     0.00  ray_caster
  0.00      7.17     0.00   288000     0.00     0.00  init_ray
  0.00      7.17     0.00   201348     0.00     0.00  sprite_compare
  0.00      7.17     0.00      708     0.00     0.00  map_get_block
  0.00      7.17     0.00      559     0.00     0.00  game_event_handler
  0.00      7.17     0.00      442     0.00     0.00  vect2dd_rotate
  0.00      7.17     0.00      360     0.00     0.00  hud_cross
  0.00      7.17     0.00      360     0.00     1.23  hud_render
  0.00      7.17     0.00      359     0.00     0.00  player_update
  0.00      7.17     0.00      177     0.00     0.00  player_collide_world
  0.00      7.17     0.00      177     0.00     0.00  player_move
  0.00      7.17     0.00        8     0.00     0.00  ft_kebab
  0.00      7.17     0.00        1     0.00     0.00  game_init_sdl
  0.00      7.17     0.00        1     0.00     0.00  map_init
  0.00      7.17     0.00        1     0.00     0.00  map_load
  0.00      7.17     0.00        1     0.00     0.00  player_init
  0.00      7.17     0.00        1     0.00     0.00  sprite_load

 %         the percentage of the total running time of the
time       program used by this function.

cumulative a running sum of the number of seconds accounted
 seconds   for by this function and those listed above it.

 self      the number of seconds accounted for by this
seconds    function alone.  This is the major sort for this
           listing.

calls      the number of times this function was invoked, if
           this function is profiled, else blank.
 
 self      the average number of milliseconds spent in this
ms/call    function per call, if this function is profiled,
	   else blank.

 total     the average number of milliseconds spent in this
ms/call    function and its descendents per call, if this 
	   function is profiled, else blank.

name       the name of the function.  This is the minor sort
           for this listing. The index shows the location of
	   the function in the gprof listing. If the index is
	   in parenthesis it shows where it would appear in
	   the gprof listing if it were to be printed.

Copyright (C) 2012 Free Software Foundation, Inc.

Copying and distribution of this file, with or without modification,
are permitted in any medium without royalty provided the copyright
notice and this notice are preserved.

		     Call graph (explanation follows)


granularity: each sample hit covers 2 byte(s) for 0.14% of 7.17 seconds

index % time    self  children    called     name
                                                 <spontaneous>
[1]    100.0    0.00    7.17                 main [1]
                0.28    5.79     360/360         game_render [2]
                0.08    0.58     360/360         game_draw_all [5]
                0.00    0.44     360/360         hud_render [7]
                0.00    0.00     559/559         game_event_handler [17]
                0.00    0.00     359/359         player_update [19]
                0.00    0.00       1/1           game_init_sdl [23]
                0.00    0.00       1/1           map_init [24]
                0.00    0.00       1/1           player_init [26]
-----------------------------------------------
                0.28    5.79     360/360         main [1]
[2]     84.6    0.28    5.79     360         game_render [2]
                4.69    0.56  288000/288000      draw_floor_and_ceil [3]
                0.34    0.01     360/360         game_draw_sprites [8]
                0.17    0.00 40312440/186117010     game_draw_pixel [4]
                0.01    0.00  288000/288000      ray_caster [12]
                0.00    0.00  288000/288000      init_ray [14]
-----------------------------------------------
                4.69    0.56  288000/288000      game_render [2]
[3]     73.3    4.69    0.56  288000         draw_floor_and_ceil [3]
                0.56    0.00 132488924/186117010     game_draw_pixel [4]
-----------------------------------------------
                0.01    0.00 3094526/186117010     game_draw_sprites [8]
                0.04    0.00 10221120/186117010     game_draw_rect [11]
                0.17    0.00 40312440/186117010     game_render [2]
                0.56    0.00 132488924/186117010     draw_floor_and_ceil [3]
[4]     11.0    0.79    0.00 186117010         game_draw_pixel [4]
-----------------------------------------------
                0.08    0.58     360/360         main [1]
[5]      9.2    0.08    0.58     360         game_draw_all [5]
                0.58    0.00     360/360         hud_put [6]
-----------------------------------------------
                0.58    0.00     360/360         game_draw_all [5]
[6]      8.1    0.58    0.00     360         hud_put [6]
-----------------------------------------------
                0.00    0.44     360/360         main [1]
[7]      6.2    0.00    0.44     360         hud_render [7]
                0.33    0.00     360/360         hud_fill [9]
                0.02    0.09     360/360         map_draw [10]
                0.00    0.00     360/360         hud_cross [13]
-----------------------------------------------
                0.34    0.01     360/360         game_render [2]
[8]      4.9    0.34    0.01     360         game_draw_sprites [8]
                0.01    0.00 3094526/186117010     game_draw_pixel [4]
-----------------------------------------------
                0.33    0.00     360/360         hud_render [7]
[9]      4.6    0.33    0.00     360         hud_fill [9]
-----------------------------------------------
                0.02    0.09     360/360         hud_render [7]
[10]     1.6    0.02    0.09     360         map_draw [10]
                0.05    0.04  635760/637200      game_draw_rect [11]
-----------------------------------------------
                0.00    0.00    1440/637200      hud_cross [13]
                0.05    0.04  635760/637200      map_draw [10]
[11]     1.3    0.05    0.04  637200         game_draw_rect [11]
                0.04    0.00 10221120/186117010     game_draw_pixel [4]
-----------------------------------------------
                0.01    0.00  288000/288000      game_render [2]
[12]     0.1    0.01    0.00  288000         ray_caster [12]
-----------------------------------------------
                0.00    0.00     360/360         hud_render [7]
[13]     0.0    0.00    0.00     360         hud_cross [13]
                0.00    0.00    1440/637200      game_draw_rect [11]
-----------------------------------------------
                0.00    0.00  288000/288000      game_render [2]
[14]     0.0    0.00    0.00  288000         init_ray [14]
-----------------------------------------------
                0.00    0.00     389/201348      sort [46]
                0.00    0.00  200959/201348      ft_sort_qck [38]
[15]     0.0    0.00    0.00  201348         sprite_compare [15]
-----------------------------------------------
                0.00    0.00     708/708         player_collide_world [20]
[16]     0.0    0.00    0.00     708         map_get_block [16]
-----------------------------------------------
                0.00    0.00     559/559         main [1]
[17]     0.0    0.00    0.00     559         game_event_handler [17]
-----------------------------------------------
                0.00    0.00     442/442         player_update [19]
[18]     0.0    0.00    0.00     442         vect2dd_rotate [18]
-----------------------------------------------
                0.00    0.00     359/359         main [1]
[19]     0.0    0.00    0.00     359         player_update [19]
                0.00    0.00     442/442         vect2dd_rotate [18]
                0.00    0.00     177/177         player_move [21]
-----------------------------------------------
                0.00    0.00     177/177         player_move [21]
[20]     0.0    0.00    0.00     177         player_collide_world [20]
                0.00    0.00     708/708         map_get_block [16]
-----------------------------------------------
                0.00    0.00     177/177         player_update [19]
[21]     0.0    0.00    0.00     177         player_move [21]
                0.00    0.00     177/177         player_collide_world [20]
-----------------------------------------------
                0.00    0.00       4/8           sprite_load [27]
                0.00    0.00       4/8           map_load [25]
[22]     0.0    0.00    0.00       8         ft_kebab [22]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[23]     0.0    0.00    0.00       1         game_init_sdl [23]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[24]     0.0    0.00    0.00       1         map_init [24]
                0.00    0.00       1/1           map_load [25]
                0.00    0.00       1/1           sprite_load [27]
-----------------------------------------------
                0.00    0.00       1/1           map_init [24]
[25]     0.0    0.00    0.00       1         map_load [25]
                0.00    0.00       4/8           ft_kebab [22]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[26]     0.0    0.00    0.00       1         player_init [26]
-----------------------------------------------
                0.00    0.00       1/1           map_init [24]
[27]     0.0    0.00    0.00       1         sprite_load [27]
                0.00    0.00       4/8           ft_kebab [22]
-----------------------------------------------

 This table describes the call tree of the program, and was sorted by
 the total amount of time spent in each function and its children.

 Each entry in this table consists of several lines.  The line with the
 index number at the left hand margin lists the current function.
 The lines above it list the functions that called this function,
 and the lines below it list the functions this one called.
 This line lists:
     index	A unique number given to each element of the table.
		Index numbers are sorted numerically.
		The index number is printed next to every function name so
		it is easier to look up where the function is in the table.

     % time	This is the percentage of the `total' time that was spent
		in this function and its children.  Note that due to
		different viewpoints, functions excluded by options, etc,
		these numbers will NOT add up to 100%.

     self	This is the total amount of time spent in this function.

     children	This is the total amount of time propagated into this
		function by its children.

     called	This is the number of times the function was called.
		If the function called itself recursively, the number
		only includes non-recursive calls, and is followed by
		a `+' and the number of recursive calls.

     name	The name of the current function.  The index number is
		printed after it.  If the function is a member of a
		cycle, the cycle number is printed between the
		function's name and the index number.


 For the function's parents, the fields have the following meanings:

     self	This is the amount of time that was propagated directly
		from the function into this parent.

     children	This is the amount of time that was propagated from
		the function's children into this parent.

     called	This is the number of times this parent called the
		function `/' the total number of times the function
		was called.  Recursive calls to the function are not
		included in the number after the `/'.

     name	This is the name of the parent.  The parent's index
		number is printed after it.  If the parent is a
		member of a cycle, the cycle number is printed between
		the name and the index number.

 If the parents of the function cannot be determined, the word
 `<spontaneous>' is printed in the `name' field, and all the other
 fields are blank.

 For the function's children, the fields have the following meanings:

     self	This is the amount of time that was propagated directly
		from the child into the function.

     children	This is the amount of time that was propagated from the
		child's children to the function.

     called	This is the number of times the function called
		this child `/' the total number of times the child
		was called.  Recursive calls by the child are not
		listed in the number after the `/'.

     name	This is the name of the child.  The child's index
		number is printed after it.  If the child is a
		member of a cycle, the cycle number is printed
		between the name and the index number.

 If there are any cycles (circles) in the call graph, there is an
 entry for the cycle-as-a-whole.  This entry shows who called the
 cycle (as parents) and the members of the cycle (as children.)
 The `+' recursive calls entry shows the number of function calls that
 were internal to the cycle, and the calls entry for each member shows,
 for that member, how many times it was called from other members of
 the cycle.

Copyright (C) 2012 Free Software Foundation, Inc.

Copying and distribution of this file, with or without modification,
are permitted in any medium without royalty provided the copyright
notice and this notice are preserved.

Index by function name

   [3] draw_floor_and_ceil    [13] hud_cross              [20] player_collide_world
  [22] ft_kebab                [9] hud_fill               [26] player_init
   [5] game_draw_all           [6] hud_put                [21] player_move
   [4] game_draw_pixel         [7] hud_render             [19] player_update
  [11] game_draw_rect         [14] init_ray               [12] ray_caster
   [8] game_draw_sprites      [10] map_draw               [15] sprite_compare
  [17] game_event_handler     [16] map_get_block          [27] sprite_load
  [23] game_init_sdl          [24] map_init               [18] vect2dd_rotate
   [2] game_render            [25] map_load
