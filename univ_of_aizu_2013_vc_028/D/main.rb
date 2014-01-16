require "yaml"

query = gets
lines = []
while line = gets
  lines.push line
end

yaml = YAML.load lines.join("\n")

list = query.split(".")
list.shift

def is_number? key
  ! ( key =~ /[a-z]/ )
end

while ! list.empty?
  key = list.shift.strip
  key = key.to_i if is_number?(key)
  if yaml.is_a?(String) || ! yaml.has_key?(key)
    yaml = nil
    break
  end
  yaml = yaml[key]
end

if yaml.is_a?(String)
  puts "string \"#{yaml}\""
elsif ! yaml.nil? && yaml.is_a?(Object)
  puts "object"
else
  puts "no such property"
end

