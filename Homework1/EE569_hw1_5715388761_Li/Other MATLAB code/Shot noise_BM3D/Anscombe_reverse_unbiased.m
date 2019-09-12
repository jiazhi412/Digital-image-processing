function output = Anscombe_reverse_unbiased(input)

[m,n] = size(input);

for i = 1:m
    for j = 1:n
        output(i,j) = pow2(input(i,j) / 2) - 0.125;
    end
end

end