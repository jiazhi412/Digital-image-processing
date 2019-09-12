E = load("Pig.mat");
for i = 1:5
    cell = E.groundTruth{i};
    groundTruth{1} = cell;
    string = "Pig" + num2str(i) + ".mat";
    save(string,'groundTruth');
end