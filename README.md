# KXemu

KXemu是一款以学习为目的开发的不同ISA的CPU模拟器，类似于大名鼎鼎的QEMU和NJUPA的NEMU。它可以用作学习计算机体系结构和操作系统，或者用于DIFFTEST。

KXemu is an educational CPU simulator for various ISAs, similar to the renowned QEMU and NJUPA's NEMU. It can be used for learning computer architecture and operating systems or for DIFFTEST.

我们是一群来自杭州电子科技大学的学生，非常喜欢计算机体系结构与操作系统。我们欢迎并希望有喜欢这些内容的同学加入我们，一起开发和维护KXemu这个项目。

We are a group of students from Hangzhou Dianzi University who are passionate about computer architecture and operating systems. We warmly welcome anyone with similar interests to join us in developing and maintaining the KXemu project.

## 使用方法 Usage

在项目的目录下运行`make menuconfig`选择编译选项和指令集，同样，使用`make run`可以直接运行`kdb`，当然，里面没有任何自带的镜像文件，你需要自己加载ELF文件。在`test`目录下，有许多已经写好的测试程序，包括了简单的CPU测试和特权级指令测试。在`docs`文件夹下面，有详细的`kdb`命令教程。

To compile `kxemu`, run `make menuconfig` in the project directory. Similarly, you can directly run `kdb` using `make run`. However, it does not include any built-in image files, so you need to load them yourself. In the `test` directory, there are various pre-written test programs, including basic CPU tests and privileged instruction tests. Detailed `kdb` command tutorials can be found in the `docs` folder.

## 功能支持 Features

现在的KXemu现在支持riscv32和riscv64指令集，所以所有编译运行选项的ISA只能指定为`riscv32`或`riscv64`。已经实现的具体细节可以在`docs`目录下的文档中查看。

Currently, KXemu supports the `riscv32` and `riscv64` instruction sets, so all compile and run options for ISA must be set to `riscv32` or `riscv64`. Specific details of the implementation can be found in the documents under the `docs` directory.

- [riscv32/64](./docs/riscv.md)

## 文件结构 File Structure

- `include` KXemu所需要的头文件。Header files required by KXemu.

- `src` KXemu的源代码。The source code of KXemu.

- `scripts` 编写KXemu需要的脚本以及KDB运行脚本。Scripts for KXemu development and KDB execution.

- `tests` 包含了KXemu的测试，大多数测试可以使用`make ISA=[isa] NAME=`(除了cpu-tests)或者`make ISA=[isa] ALL=`(cpu-tests)的方法运行。Contains tests for KXemu. Most tests can be run using `make ISA=[isa] NAME=` (except for CPU tests) or `make ISA=[isa] ALL=` (for CPU tests).

- `utils` 辅助KXemu的工具，但是没有这些工具KXemu同样可以正常运行。Tools to assist KXemu, though KXemu can run normally without them.

## 贡献

因为这是一个开源的学习项目，而我们也只是学生，所以我们非常期待你能够对我们的代码提出建议或者完善一些功能。你可以直接fork我们的仓库，在修改后提出PR，我们会在1到2天内回复。如果你是杭州电子科技大学的学生，你可以直接联系杭州电子科技大学 **计算机科学与技术协会(计科协)**，我们可以共同探讨。我们创立这个项目的初衷，一是想继续学习，二是在NEMU上直接修改过于麻烦。

As this is an open-source learning project and we are still students, we highly value your suggestions or contributions to improve the codebase. You can fork our repository and submit a PR after making changes; we will respond within 1-2 days. If you are a student at Hangzhou Dianzi University, feel free to contact the **HDU-CSKX**, and we can explore ideas together. The purpose of this project is to continue learning and address the challenges of directly modifying NEMU.

### 联系我们 Contact Us

邮箱：ziyou@hdu.edu.cn (预计会在1周之内回复，如果你是校内的同学直接找计科协的系统组应该会更快。)

Email: ziyou@hdu.edu.cn (We will respond within one week. If you are a student at Hangzhou Dianzi University, contacting the Systems Group of the Computer Science Association directly might be faster.)

## 我们目前的计划 Our Current Plans

1. 大致完成riscv32的特权级指令，达到启动xv6的要求。Complete privileged instructions for `riscv32` to meet the requirements of booting xv6.  

2. 在1月份将riscv32迁移至riscv64，并启动xv6。Migrate `riscv32` to `riscv64` by January and boot xv6. 

3. 提供一套合理且完整的将KXemu用作difftest的方案。Provide a comprehensive solution to use KXemu for DIFFTEST.

4. 对LoongArch和x86指令集进行支持。Add support for LoongArch and x86 instruction sets.

## 声明 Disclaimer

如果你需要将本项目用于比赛或者商业盈利性活动，那么你**必须在显著位置**标明本项目的主要贡献者(如果我们更新了)和开源链接。

If you wish to use this project for competitions or commercial profit-driven activities, you **must prominently credit** the main contributors of this project (if updated) and include the open-source link.

## 主要贡献者 Main Contributors
