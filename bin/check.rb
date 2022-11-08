#!/bin/ruby

homed = '/Users/richmit';
mrsrc = '/Users/richmit/world/my_prog/mraster'

#        Thingy                                              This Depends on Thingy
deps = { 
         "#{mrsrc}/README.org"                            => "#{mrsrc}/docs/index.org",
         "#{mrsrc}/examples/BurningShip.cpp"              => "#{homed}/Documents/WWW/site/SS/BurningShip/index.org",
         "#{mrsrc}/examples/apollony.cpp"                 => "#{homed}/Documents/WWW/site/SS/AGasket/index.org",
         "#{mrsrc}/examples/apomorph.cpp"                 => "#{homed}/Documents/WWW/site/SS/AGasket/index.org",
         "#{mrsrc}/examples/biomorphMorph.cpp"            => "#{homed}/Documents/WWW/site/SS/biomorphMorph/index.org",
         "#{mrsrc}/examples/chaos_game.cpp"               => "#{homed}/Documents/WWW/site/SS/ChaosGame/index.org",
         "#{mrsrc}/examples/circles.cpp"                  => "#{homed}/Documents/WWW/site/SS/circles2/index.org",
         "#{mrsrc}/examples/collatz.cpp"                  => "#{homed}/Documents/WWW/site/SS/collatz/index.org",
         "#{mrsrc}/examples/julia.cpp"                    => "#{homed}/Documents/WWW/site/SS/julia/index.org",
         "#{mrsrc}/examples/juliaM.cpp"                   => "#{homed}/Documents/WWW/site/SS/julia/index.org",
         "#{mrsrc}/examples/juliaM2.cpp"                  => "#{homed}/Documents/WWW/site/SS/julia/index.org",
         "#{mrsrc}/examples/mandelbrot_biomorph.cpp"      => "#{homed}/Documents/WWW/site/SS/mandelbrotBiomorph/index.org",
         "#{mrsrc}/examples/mandelbrot_bm_cplx.cpp"       => "#{homed}/Documents/WWW/site/SS/mandelbrot/index.org",
         "#{mrsrc}/examples/mandelbrot_ltrap.cpp"         => "#{homed}/Documents/WWW/site/SS/mandelbrotLtrap/index.org",
         "#{mrsrc}/examples/mandelbrot_pickover.cpp"      => "#{homed}/Documents/WWW/site/SS/mandelbrotLtrap/index.org",
         "#{mrsrc}/examples/mandelbrot_potential.cpp"     => "#{homed}/Documents/WWW/site/SS/mandelbrot/index.org",
         "#{mrsrc}/examples/mandelbrot_potential_b_0.pov" => "#{homed}/Documents/WWW/site/SS/mandelbrot/index.org",
         "#{mrsrc}/examples/mandelbrot_simple.cpp"        => "#{homed}/Documents/WWW/site/SS/mandelbrot/index.org",
         "#{mrsrc}/examples/mandelbrot_wave.cpp"          => "#{homed}/Documents/WWW/site/SS/mandelbrotWave/index.org",
         "#{mrsrc}/examples/multibrotMovie.cpp"           => "#{homed}/Documents/WWW/site/SS/multibrot/index.org",
         "#{mrsrc}/examples/multibrotSnaps.cpp"           => "#{homed}/Documents/WWW/site/SS/multibrot/index.org",

         "#{mrsrc}/examples/laguerre_3updown.cpp"         => "#{homed}/Documents/WWW/site/SS/newton/index.html",
         "#{mrsrc}/examples/newton_3updown.cpp"           => "#{homed}/Documents/WWW/site/SS/newton/index.html",
         "#{mrsrc}/examples/newton_half.cpp"              => "#{homed}/Documents/WWW/site/SS/newton/index.html",
         "#{mrsrc}/examples/newton_max_back.cpp"          => "#{homed}/Documents/WWW/site/SS/newton/index.html",
         "#{mrsrc}/examples/newton_max_mod.cpp"           => "#{homed}/Documents/WWW/site/SS/newton/index.html",
         "#{mrsrc}/examples/newton_min_angle.cpp"         => "#{homed}/Documents/WWW/site/SS/newton/index.html",
         "#{mrsrc}/examples/newton_min_root.cpp"          => "#{homed}/Documents/WWW/site/SS/newton/index.html",
         "#{mrsrc}/examples/newton_modified.cpp"          => "#{homed}/Documents/WWW/site/SS/newton/index.html",
         "#{mrsrc}/examples/newton_orbits.cpp"            => "#{homed}/Documents/WWW/site/SS/newton/index.html",
         "#{mrsrc}/examples/newton_roter.cpp"             => "#{homed}/Documents/WWW/site/SS/newton/index.html",
         "#{mrsrc}/examples/newton_simple.cpp"            => "#{homed}/Documents/WWW/site/SS/newton/index.html",
         "#{mrsrc}/examples/newton_z6.cpp"                => "#{homed}/Documents/WWW/site/SS/newton/index.html",

         "#{mrsrc}/examples/peterdejong.cpp"              => "#{homed}/Documents/WWW/site/SS/swirl/index.org",
         "#{mrsrc}/examples/peterdejongM.cpp"             => "#{homed}/Documents/WWW/site/SS/swirl/index.org",
         "#{mrsrc}/examples/pickoverPopcorn.cpp"          => "#{homed}/Documents/WWW/site/SS/PickoverPopcorn/index.org",
         "#{mrsrc}/examples/sic.cpp"                      => "#{homed}/Documents/WWW/site/SS/sic/index.org",
         "#{mrsrc}/examples/sic_search.cpp"               => "#{homed}/Documents/WWW/site/SS/sic/index.org",
         "#{mrsrc}/examples/tippets.cpp"                  => "#{homed}/Documents/WWW/site/SS/tippets/index.org",
         "#{mrsrc}/examples/tricorn.cpp"                  => "#{homed}/Documents/WWW/site/SS/tricorn/index.org",
         "#{mrsrc}/examples/tricornMovie.cpp"             => "#{homed}/Documents/WWW/site/SS/tricorn/index.org",
         "#{mrsrc}/lib/hello.cpp"                         => "#{mrsrc}/docs/QuickStart.org"
       };

deps.each do |aFile, bFile|
  begin
    aStat = File::Stat.new(aFile);
    bStat = File::Stat.new(bFile);
    if (aStat.mtime > bStat.mtime) then
      puts("OUT OF DATE: #{bFile}    (#{aFile})")
    else
      if (false) then
        puts("GOOD       : #{bFile}")
      end
    end
  rescue
    puts("ERROR: Something went wrong with #{aFile} => #{bFile}");
  end
end
