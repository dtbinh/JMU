# Author: Conner Turnbull
class Huffman
  class Node
    def initialize(character, count)
      @character = character
      @count = count
      @left = nil
      @right = nil
      @encoding = nil 
    end

    attr_accessor :character, :count, :left, :right, :encoding
  end

  # Must create an internal Huffman tree for the given text and from this an 
  # encoding table. No Huffman tree and an empty encoding table must be created
  # for a text of less than two characters.
  def initialize(text)
    @text = text
    @head = tree(text)
    @table = Hash.new
    table()
  end

  # Must return the string provided as the constructor argument
  def text
    @text
  end

  # Must return a Huffman coding table as a hash whose keys are the characters
  # from the constructor argument text, and whose values are the Huffman
  # encodings for the characters as strings of 0 and 1 characters
  # (bit strings). The table must produce the empty string (not nil) when
  # indexed with a character missing from the constructor text argument.
  def table
    table_helper("", @head)
    return @table
  end

  # Must encode the given text (or the text provided as the constructor
  # argument if no argument is given) into a bit string using the class' coding
  # table and return it. Note that if a text is provided as a parameter, it may
  # contain characters missing from the class' coding table. Any such
  # characters must be ignored in the encoding process; that is, they are
  # treated as if they did not exist.
  def encode(text = nil)
    _text = text
    _encoding = ""
    if _text == nil
      _text = @text
    end

    _text.split("").each do |ch|
      if @table[ch] != nil
        _encoding += @table[ch]
      end
    end

    return _encoding
  end

  # Must decode the bit_string using the class' Huffman encoding tree. Note
  # that any bit string can be decoded using a Huffman tree, but it may have
  # some extra bits on the end. Any terminal bits that do not translate to a
  # character (that is, they do not define a path from the root all the way to
  # a leaf) must be ignored.
  def decode(bit_string)
    _bit_string = bit_string.reverse
    _result = ""
    _cur = @head
    while 0 < _bit_string.length
      if _cur.character == nil
        if _bit_string[_bit_string.length-1] == "0"
          _cur = _cur.left
          _bit_string.chop!
          if _cur.character != nil
            _result += _cur.character
            _cur = @head
          end
        else
          _cur = _cur.right
          _bit_string.chop!
          if _cur.character != nil
            _result += _cur.character
            _cur = @head
          end
        end
      end
    end
    return _result
  end

  # Must return a Huffman tree from the given text (or the text provided as the
  # constructor argument text if no argument is given).
  def tree(text = nil)
    _text = text
    _hash = Hash.new
    _tree = Array.new

    if _text == nil
      _text = @text
    end

    _text.split("").each do |ch|
      if _hash[ch] == nil
        _hash[ch] = 1
      elsif
        _hash[ch] += 1
      end
    end

    _hash.sort_by{|k, v| v}.reverse.each do |key_value|
      _tree.push(Node.new(key_value[0], key_value[1]))
    end


    while 1 < _tree.length
      _left = _tree.pop
      _right = _tree.pop
      _node = Node.new(nil, _left.count + _right.count)
      _node.left = _left
      _node.right = _right
      _tree.push(_node)
      _tree = _tree.sort_by {|node| node.count}.reverse
    end

    return _tree.pop
  end

  # Traverses the tree using preorder recursion and adds the encoding for each
  # terminal node to its respective node.
  def table_helper(tail, node)
    _tail = tail
    if node.character != nil
      @table[node.character] = tail
      return
    end
    table_helper(tail + "0", node.left)
    table_helper(tail + "1", node.right)
  end
  #private :tree, :table_helper
end
