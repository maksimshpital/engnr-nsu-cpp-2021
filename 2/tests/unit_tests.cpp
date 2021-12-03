#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "../CommandCreator.h"
#include "../Command.h"
#include "../Context.h"


TEST(TestCommands, test_pop_command) {
    Context ctx;
    CommandCreator creator;
    std::string command = "PUSH 3";
    creator.proceed(command, ctx);
    command = "PUSH 5";
    creator.proceed(command, ctx);
    command = "POP";
    creator.proceed(command, ctx);
    ASSERT_EQ(ctx.stack.size(), 1);
    ASSERT_EQ(ctx.stack.top(), 3);
}

TEST(TestCommands, test_push_command){
    Context ctx;
    CommandCreator creator;
    std::string command = "PUSH 3";
    creator.proceed(command, ctx);
    command = "PUSH 4";
    creator.proceed(command, ctx);
    ASSERT_EQ(ctx.stack.size(), 2);
    ASSERT_EQ(ctx.stack.top(), 4);
}

TEST(TestCommands, test_peek_push_var_command) {
    Context ctx;
    CommandCreator creator;
    std::string command = "PUSH 7";
    creator.proceed(command, ctx);
    command = "PEEK test_var";
    creator.proceed(command, ctx);
    command = "POP";
    creator.proceed(command, ctx);
    ASSERT_EQ(ctx.stack.size(), 0);
    command = "PUSH test_var";
    creator.proceed(command, ctx);
    ASSERT_EQ(ctx.stack.top(), 7);
    ASSERT_EQ(ctx.stack.size(),1);
}

TEST(TestCommands, test_abs_command) {
    Context ctx;
    CommandCreator creator;
    std::string command = "PUSH -9";
    creator.proceed(command, ctx);
    command = "ABS";
    creator.proceed(command, ctx);
    ASSERT_EQ(ctx.stack.size(), 1);
    ASSERT_EQ(ctx.stack.top(), 9);
}

TEST(TestCommands, test_plus_command) {
    Context ctx;
    CommandCreator creator;
    std::string command = "PUSH 7";
    creator.proceed(command, ctx);
    command = "PUSH 8";
    creator.proceed(command, ctx);
    command = "PLUS";
    creator.proceed(command, ctx);
    ASSERT_EQ(ctx.stack.size(), 1);
    ASSERT_EQ(ctx.stack.top(), 15);
}

TEST(TestCommands, test_minus_command) {
    Context ctx;
    CommandCreator creator;
    std::string command = "PUSH 90";
    creator.proceed(command, ctx);
    command = "PUSH 88";
    creator.proceed(command, ctx);
    command = "MINUS";
    creator.proceed(command, ctx);
    ASSERT_EQ(ctx.stack.size(), 1);
    ASSERT_EQ(ctx.stack.top(), 2);
}

TEST(TestCommands, test_mul_command){
    Context ctx;
    CommandCreator creator;
    std::string command = "PUSH 6";
    creator.proceed(command, ctx);
    command = "PUSH 7";
    creator.proceed(command, ctx);
    command = "MUL";
    creator.proceed(command, ctx);
    ASSERT_EQ(ctx.stack.size(), 1);
    ASSERT_EQ(ctx.stack.top(), 42);
}

TEST(TestCommands, test_div_command){
    Context ctx;
    CommandCreator creator;
    std::string command = "PUSH 8";
    creator.proceed(command, ctx);
    command = "PUSH 2";
    creator.proceed(command, ctx);
    command = "DIV";
    creator.proceed(command, ctx);
    ASSERT_EQ(ctx.stack.size(), 1);
    ASSERT_EQ(ctx.stack.top(), 4);
}

TEST(TestSuccess, test_success) {
    Context ctx;
    CommandCreator creator;
    std::string command = "PUSH -14";
    creator.proceed(command, ctx);
    command = "PUSH 5";
    creator.proceed(command, ctx);
    command = "DIV";
    creator.proceed(command, ctx);
    command = "PEEK test_var";
    creator.proceed(command, ctx);
    command = "POP";
    creator.proceed(command, ctx);
    command = "# PRINT (9 - test_var) * 20";
    creator.proceed(command, ctx);

    command = "PUSH 9";
    creator.proceed(command, ctx);
    command = "PUSH test_var";
    creator.proceed(command, ctx);
    command = "MINUS";
    creator.proceed(command, ctx);
    command = "PUSH 20";
    creator.proceed(command, ctx);
    command = "MUL";
    creator.proceed(command, ctx);
    ASSERT_EQ(ctx.stack.top(), 220);
}

TEST(TestException, test_bad_input_exception) {
    Context ctx;
    CommandCreator creator;
    std::string command = "PUSH 9999999999999999999";
    try{
        creator.proceed(command, ctx);
    }catch (BadInputException &exception) {
        ASSERT_TRUE(true);
        return;
    }
    ASSERT_TRUE(false);
}

TEST(TestException, test_overflow_exception) {
    Context ctx;
    CommandCreator creator;
    std::string command = "PUSH 99999";
    creator.proceed(command, ctx);
    creator.proceed(command, ctx);
    try{
        command = "MUL";
        creator.proceed(command, ctx);
    }catch (OverflowException &exception) {
        ASSERT_TRUE(true);
        return;
    }
    ASSERT_TRUE(false);
}

TEST(TestException, test_empty_stack_exception) {
    Context ctx;
    CommandCreator creator;
    std::string command = "PUSH 89";
    creator.proceed(command, ctx);
    command = "POP";
    creator.proceed(command, ctx);
    try{
        creator.proceed(command, ctx);
    }catch (EmptyStack &exception) {
        ASSERT_TRUE(true);
        return;
    }
    ASSERT_TRUE(false);
}

TEST(TestException, test_incorrect_stack_depth) {
    Context ctx;
    CommandCreator creator;
    std::string command = "PUSH 100";
    try{
        command = "MUL";
        creator.proceed(command, ctx);
    }catch (IncorrectStackDepth &exception) {
        ASSERT_TRUE(true);
        return;
    }
    ASSERT_TRUE(false);
}

TEST(TestException, test_bad_command) {
    Context ctx;
    CommandCreator creator;
    std::string command = "NON_EXIST_CMD";
    try{
        creator.proceed(command, ctx);
    }catch(BadCommand &exception){
        ASSERT_TRUE(true);
        return;
    }
    ASSERT_TRUE(false);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
