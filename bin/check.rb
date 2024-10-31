#!/bin/ruby

# Find all references to mraster code on my web page, and list org files that are older than the code they reference.

require 'set'
require 'find'
require 'fileutils' 

refs = Hash.new
Find.find(File.join(ENV['HOME'], 'Documents', 'WWW', 'site', 'SS')) do |path|
  if File.basename(path).match('.*\.org$') then
    open(path, "r") do |file|
      file.each_line do |line|
        if (tmp = line.match('^(.*)(~\/world\/my_prog\/mraster\/examples\/[a-zA-Z0-1_-]+.cpp)(.*)$')) then
          ref = File.expand_path(tmp[2])
          if ( !(refs.member?(path))) then
            refs[path] = Set.new
          end
          refs[path].add(ref)
        end
      end
    end
  end
end

refs.each do |k, v|
  if (! (FileUtils.uptodate?(k, v))) then
    puts(k)
    v.each do |r|
      if ( !(FileUtils.uptodate?(k, [r]))) then
        puts(" NEWER: #{r}")
      end
    end
  end
end
