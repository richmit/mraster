#!/bin/ruby

homed = '/Users/richmit';
mrsrc = '/Users/richmit/world/my_prog/mraster'

#        Thingy                                              This Depends on Thingy
deps = { "#{mrsrc}/examples/BurningShip.cpp"              => "#{homed}/world/WWW/site/SS/BurningShip/index.org",
         "#{mrsrc}/examples/apollony.cpp"                 => "#{homed}/world/WWW/site/SS/AGasket/index.org",
         "#{mrsrc}/examples/BurningShip.cpp"              => "#{homed}/world/WWW/site/SS/BurningShip/index.org",
         "#{mrsrc}/examples/mandelbrot_bm_cplx.cpp"       => "#{homed}/world/WWW/site/SS/mandelbrot/index.org",
         "#{mrsrc}/examples/mandelbrot_potential.cpp"     => "#{homed}/world/WWW/site/SS/mandelbrot/index.org",
         "#{mrsrc}/examples/mandelbrot_potential_b_0.pov" => "#{homed}/world/WWW/site/SS/mandelbrot/index.org",
         "#{mrsrc}/examples/newton_bm_cplx.cpp"           => "#{homed}/world/WWW/site/SS/newton/index.org",
         "#{mrsrc}/examples/newton_max_mod.cpp"           => "#{homed}/world/WWW/site/SS/newton/index.org",
         "#{mrsrc}/examples/multibrotMovie.cpp"           => "#{homed}/world/WWW/site/SS/multibrot/index.org",
         "#{mrsrc}/examples/multibrotSnaps.cpp"           => "#{homed}/world/WWW/site/SS/multibrot/index.org",
         "#{mrsrc}/examples/tricorn.cpp"                  => "#{homed}/world/WWW/site/SS/tricorn/index.org",
         "#{mrsrc}/README.org"                            => "#{mrsrc}/docs/index.org",
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
