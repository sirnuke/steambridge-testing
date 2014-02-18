#!/usr/bin/env ruby
# convert.rb - Ruby tool for generating the wrapping classes

def err(msg)
  puts "#{$0}: #{msg}"
  exit(1)
end

class API
  attr_accessor :ret, :name, :args

  def initialize(line, num)
    @ret = nil
    @name = nil
    @args = []
    arg = nil
    line.scan(/\S+/) do |token|
      token.sub!(/[\(\),]/, '')
      next if token.empty?
      if @ret.nil?
        @ret = token
      elsif @name.nil?
        @name = token
      elsif arg.nil?
        arg = token
      else
        @args << { :ret => arg, :name => token }
        arg = nil
      end
    end
    if @ret.nil? or @name.nil?
      err "Error on line #{num} - missing return or name"
    end
  end

  def to_s
    res = "#{@ret}: #{@name}\t("
    @args.each do |arg|
      res += "\t" unless arg == @args.first
      res += "#{arg[:ret]}: #{arg[:name]}"
    end
    res += ")"
    return res
  end
end

err "Requires one argument, the spec filename." if ARGV.count == 0
file = ARGV[0]
err "#{file} doesn't exist!" unless File.exist?(file)

name = nil
apis = []
num = 0

File.open(file, 'r') do |file|
  file.each_line do |line|
    num += 1
    line.strip!
    next if line.empty?
    if name.nil?
      name = line
      next
    end
    apis << API.new(line, num)
  end
end

puts "Name is #{name}"
apis.each { |api| puts api.to_s }

