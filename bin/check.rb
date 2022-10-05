#!/bin/ruby

homed = '/Users/richmit';
mrsrc = '/Users/richmit/world/my_prog/mraster'

#        Thingy                                              This Depends on Thingy
deps = { 
         "#{mrsrc}/README.org"                            => "#{mrsrc}/docs/index.org",
         "#{mrsrc}/lib/hello.cpp"                         => "#{mrsrc}/docs/QuickStart.org",
         "#{mrsrc}/examples/BurningShip.cpp"              => "#{homed}/world/WWW/site/SS/BurningShip/index.org",
         "#{mrsrc}/examples/apollony.cpp"                 => "#{homed}/world/WWW/site/SS/AGasket/index.org",
         "#{mrsrc}/examples/apomorph.cpp"                 => "#{homed}/world/WWW/site/SS/AGasket/index.org",
         "#{mrsrc}/examples/biomorphMorph.cpp"            => "#{homed}/world/WWW/site/SS/biomorphMorph/index.org",
         "#{mrsrc}/examples/chaos_game.cpp"               => "#{homed}/world/WWW/site/SS/ChaosGame/index.org",
         "#{mrsrc}/examples/circles.cpp"                  => "#{homed}/world/WWW/site/SS/circles2/index.org",
         "#{mrsrc}/examples/collatz.cpp"                  => "#{homed}/world/WWW/site/SS/collatz/index.org",
         "#{mrsrc}/examples/mandelbrot_biomorph.cpp"      => "#{homed}/world/WWW/site/SS/mandelbrotBiomorph/index.org",
         "#{mrsrc}/examples/mandelbrot_bm_cplx.cpp"       => "#{homed}/world/WWW/site/SS/mandelbrot/index.org",
         "#{mrsrc}/examples/mandelbrot_potential.cpp"     => "#{homed}/world/WWW/site/SS/mandelbrot/index.org",
         "#{mrsrc}/examples/mandelbrot_potential_b_0.pov" => "#{homed}/world/WWW/site/SS/mandelbrot/index.org",
         "#{mrsrc}/examples/mandelbrot_simple.cpp"        => "#{homed}/world/WWW/site/SS/mandelbrot/index.org",
         "#{mrsrc}/examples/mandelbrot_wave.cpp"          => "#{homed}/world/WWW/site/SS/mandelbrotWave/index.org",
         "#{mrsrc}/examples/julia.cpp"                    => "#{homed}/world/WWW/site/SS/julia/index.org",
         "#{mrsrc}/examples/juliaM2.cpp"                  => "#{homed}/world/WWW/site/SS/julia/index.org",
         "#{mrsrc}/examples/juliaM.cpp"                   => "#{homed}/world/WWW/site/SS/julia/index.org",
         "#{mrsrc}/examples/multibrotMovie.cpp"           => "#{homed}/world/WWW/site/SS/multibrot/index.org",
         "#{mrsrc}/examples/multibrotSnaps.cpp"           => "#{homed}/world/WWW/site/SS/multibrot/index.org",
         "#{mrsrc}/examples/newton_bm_cplx.cpp"           => "#{homed}/world/WWW/site/SS/newton/index.org",
         "#{mrsrc}/examples/newton_max_mod.cpp"           => "#{homed}/world/WWW/site/SS/newton/index.org",
         "#{mrsrc}/examples/peterdejong.cpp"              => "#{homed}/world/WWW/site/SS/swirl/index.org",
         "#{mrsrc}/examples/peterdejongM.cpp"             => "#{homed}/world/WWW/site/SS/swirl/index.org",
         "#{mrsrc}/examples/pickoverPopcorn.cpp"          => "#{homed}/world/WWW/site/SS/PickoverPopcorn/index.org",
         "#{mrsrc}/examples/sic.cpp"                      => "#{homed}/world/WWW/site/SS/sic/index.org",
         "#{mrsrc}/examples/sic_search.cpp"               => "#{homed}/world/WWW/site/SS/sic/index.org",
         "#{mrsrc}/examples/tippets.cpp"                  => "#{homed}/world/WWW/site/SS/tippets/index.org",
         "#{mrsrc}/examples/tricorn.cpp"                  => "#{homed}/world/WWW/site/SS/tricorn/index.org",
         "#{mrsrc}/examples/tricornMovie.cpp"             => "#{homed}/world/WWW/site/SS/tricorn/index.org"
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
