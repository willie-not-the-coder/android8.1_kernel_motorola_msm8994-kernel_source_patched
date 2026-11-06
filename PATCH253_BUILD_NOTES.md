# Patch253 Stage06 build notes

Functional patch
- `drivers/media/platform/msm/camera_v2/msm.c`
- `drivers/media/platform/msm/camera_v2/camera/camera.c`

The final kernel was built as AArch64 using the supplied kernel tree and Patch253.
The build host did not provide the tree's expected Android GCC 4.9/Python-2/bc environment,
so the source tree also contains narrowly-scoped compatibility edits required to build this
legacy tree with Clang 17/Python 3. These are host/build compatibility changes, not part of
Patch253's camera behavior.

See `build_compat_changes.txt` in the associated release workspace/archive for the original
compatibility inventory. The packaged source excludes the Kbuild `out/` directory.

Verified kernel payload SHA-256:
`8902703bbb6e35f834bb0fb6d099e0e101f6a88422e69610a513a5142612fd78`

Verified Stage06 strings:
- `QCamP253_KPOST`
- `QCamP253_KSTATUS`
- `QCamP253_KPOST: NOTIMEOUT=0xffffffff`
