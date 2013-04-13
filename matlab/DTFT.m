M = 8;
w = linspace(-2*pi, 2*pi, 800);
X_dtft = (sin(w*M/2) ./ sin(w/2)) .* exp(-1j * w * (M-1) / 2);
plot(w, abs(X_dtft))
title('|X(\omega)|')