function output = Anscombe_reverse_biased(input)

[m,n] = size(input);

for i = 1:m
    for j = 1:n
        output(i,j) = (input(i,j) / 2)^2 - 0.375;
    end
end

end