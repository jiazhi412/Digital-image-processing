filename_noisy = "G:\569\HW1_images\HW1_images\pepper_dark_noise.raw";
filename_noisefree = "G:\569\HW1_images\HW1_images\pepper_dark.raw";
noisy = readraw(filename_noisy);
noisefree = readraw(filename_noisefree);
noisy_Anscombe = Anscombe_forward(noisy);

minimum = min(min(noisy_Anscombe));
maximum = max(max(noisy_Anscombe));

z = (noisy_Anscombe - minimum) / (maximum - minimum);
for i = 1 : 20
sigma = i;
[PSNR, y_est] = BM3D(1, z, sigma);
noisy_est = y_est * (maximum - minimum) + minimum;

result = Anscombe_reverse_biased(noisy_est);

filename_save = "G:\569\HW1_images\Image_result\pepper_dark_BM3D_"+ num2str(sigma) +".raw";
count = writeraw(result, filename_save);
end

% psnr(result,noisefree)

filtered = readraw(filename_save);


