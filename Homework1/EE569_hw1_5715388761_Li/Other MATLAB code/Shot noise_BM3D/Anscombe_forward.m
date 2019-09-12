function output = Anscombe_forward(input)

[m,n] = size(input);

for i = 1:m
    for j = 1:n
        output(i,j) = sqrt(input(i,j) + 0.375) * 2;
    end
end

end