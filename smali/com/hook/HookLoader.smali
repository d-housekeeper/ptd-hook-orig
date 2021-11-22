.class public Lcom/hook/HookLoader;
.super Ljava/lang/Object;
.source "HookLoader.java"


# static fields
.field private static loaded:Z


# direct methods
.method static constructor <clinit>()V
    .locals 1

    .line 4
    const/4 v0, 0x0

    sput-boolean v0, Lcom/hook/HookLoader;->loaded:Z

    return-void
.end method

.method public constructor <init>()V
    .locals 0

    .line 3
    invoke-direct {p0}, Ljava/lang/Object;-><init>()V

    return-void
.end method

.method private static native initHook()V
.end method

.method public static loadLib()V
    .locals 1

    .line 8
    sget-boolean v0, Lcom/hook/HookLoader;->loaded:Z

    if-eqz v0, :cond_0

    return-void

    .line 9
    :cond_0
    const-string v0, "hook"

    invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V

    .line 10
    const/4 v0, 0x1

    sput-boolean v0, Lcom/hook/HookLoader;->loaded:Z

    .line 11
    return-void
.end method
