clear all
close all

load('../../cpp/imfs.mat')
load('../dat/100.mat')

t = tm(1:250,:);
s = signal(1:250,1);

imfs = emd(s);

figure

subplot(2,1,1)
plot(t,s,t,emd_filter(imfs,1))
grid on
legend('Original signal', '1 IMF discarded - MATLAB')
ylabel('Amplitude')

subplot(2,1,2)
plot(t,s,t,emd_filter(data',1))
grid on
legend('Original signal', '1 IMF discarded - c++')
ylabel('Amplitude')
xlabel('Time [s]')

figure

subplot(2,1,1)
plot(t,s,t,emd_filter(imfs,2))
grid on
legend('Original signal', '2 IMF discarded - MATLAB')
ylabel('Amplitude')

subplot(2,1,2)
plot(t,s,t,emd_filter(data',2))
grid on
legend('Original signal', '2 IMF discarded - c++')
ylabel('Amplitude')
xlabel('Time [s]')

load('maxenv.mat')
load('../../cpp/env.mat')

figure

plot(t, maxenv, t, vec2)
grid on
legend('MATLAB spline', 'Eigen spline')
ylabel('Amplitude')
xlabel('Time [s]')
