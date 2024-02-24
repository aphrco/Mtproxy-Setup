# MTProxy
نصب و راه اندازی  MT-Proto proxy

## Building
کد های زیر را بر اساس سیستم عامل وارد کنین 
برای  Debian/Ubuntu:
```bash
apt install git curl build-essential libssl-dev zlib1g-dev
```
برای  CentOS/RHEL:
```bash
yum install openssl-devel zlib-devel
yum groupinstall "Development Tools"
```

باید فایل را با دستور زیر به سرور منتقل کنید و وارد ریشه ی MTProxy شوید :
```bash
git clone https://github.com/TelegramMessenger/MTProxy
cd MTProxy
```

با استفاده از دستور زیر فولدر های مورد نیاز را اجرا کنید 
```bash
make && cd objs/bin
```

اگر مشکل بر خوردید ابتدا بررسی کنید که فایل objs/bin وجود دارد یا خیر و اگر وجود داشت حذف کنین 
## Running
برای اجرا نیاز به کد سکرت دارید که با دستورات زیر این کد برای شما ساخته میشود : 
```bashcurl -s https://core.telegram.org/getProxySecret -o proxy-secret
```
```bash
curl -s https://core.telegram.org/getProxyConfig -o proxy-multi.conf
```
```bash
head -c 16 /dev/urandom | xxd -ps
```
کد در این مرحله برای شما ساخته میشود و باید در مکانی ذخیره کنید 

و با دستور زیر میتوانید پروکسی خود را اجرا کنید : 
```bash
./mtproto-proxy -u nobody -p 8888 -H 443 -S <secret> --aes-pwd proxy-secret proxy-multi.conf -M 1
```


دستور - `nobody` نام کاربری است. `mtproto-proxy` فراخوانی `setuid()` را برای رها کردن امتیازات انجام می‌دهد.

دستور - `443` پورت است که توسط مشتریان برای اتصال به پروکسی استفاده می‌شود.

دستور - `8888` پورت محلی است. شما می‌توانید از آن برای دریافت آمار از `mtproto-proxy` استفاده کنید. مانند `wget localhost:8888/stats`. شما فقط می‌توانید این آمار را از طریق اتصال محلی دریافت کنید.

دستور - `<secret>` رمزی است که در مرحله ۳ تولید شده است. همچنین می‌توانید چندین رمز تنظیم کنید: `-S <secret1> -S <secret2>`.

دستور - `proxy-secret` و `proxy-multi.conf` در مراحل ۱ و ۲ به دست می‌آیند.

دستور  - `1` تعداد کارگران است. می‌توانید تعداد کارگران را افزایش دهید، اگر سرور قدرتمندی دارید.

همچنین میتوانید  سایر گزینه‌ها را با استفاده از `mtproto-proxy --help` بررسی کنید.

۵. لینک را با طرح زیر تولید کنید: `tg://proxy?server=SERVER_NAME&port=PORT&secret=SECRET` (یا به ربات رسمی اجازه دهید آن را برای شما تولید کند).
۶. پروکسی خود را با [@MTProxybot](https://t.me/MTProxybot) در تلگرام ثبت کنید.
۷. تگ دریافتی خود را با آرگومان‌های زیر تنظیم کنید: `-P <proxy tag>`
۸. لذت ببرید.
پروکسی تا زمانی فعال است که بر روی سرور ران باشد و یا میتوانید از طریق مراحل زیر برای پروکسی خود سرویس ایجاد کنید که به صورت دائمی فعال باشد :

```bash
nano /etc/systemd/system/MTProxy.service
```
2. Edit this basic service (especially paths and params):
```bash
[Unit]
Description=MTProxy
After=network.target

[Service]
Type=simple
WorkingDirectory=/opt/MTProxy
ExecStart=/opt/MTProxy/mtproto-proxy -u nobody -p 8888 -H 443 -S <secret> -P <proxy tag> <other params>
Restart=on-failure

[Install]
WantedBy=multi-user.target
```
3. Reload daemons:
```bash
systemctl daemon-reload
```
4. Test fresh MTProxy service:
```bash
systemctl restart MTProxy.service
# Check status, it should be active
systemctl status MTProxy.service
```
5. Enable it, to autostart service after reboot:
```bash
systemctl enable MTProxy.service
```

## Docker image
Telegram is also providing [official Docker image](https://hub.docker.com/r/telegrammessenger/proxy/).
Note: the image is outdated.
