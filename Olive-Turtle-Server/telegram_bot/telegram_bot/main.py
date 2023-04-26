import configuration
import logging
import json
from telegram import Update, Chat, InlineKeyboardButton, InlineKeyboardMarkup
from telegram.ext import (
    filters,
    MessageHandler,
    ApplicationBuilder,
    CommandHandler,
    ContextTypes,
    Application,
    CallbackQueryHandler,
    ConversationHandler,
)

logging.basicConfig(
    format="%(asctime)s - %(name)s - %(levelname)s - %(message)s",
    level=logging.INFO)

i = 0
# Meta states
STOPPING, SHOWING = map(chr, range(i, i + 2))
i += 2

# Common states
SELECTING_ACTION = map(chr, range(i, i + 1))
i += 1

GRANT_ACCESS, REVOKE_ACCESS = map(chr, range(i, i + 2))
i += 2

# Different constants for this example
(
    USER,
    CHAT,
    START_OVER,
) = map(chr, range(i, i + 3))

# Shortcut for ConversationHandler.END
END = ConversationHandler.END


# async def authenticate(update: Update, context: ContextTypes.DEFAULT_TYPE):
# 	msg = f"Access denied. Please either authorize user {update.effective_user.id} or chat {update.effective_chat.id}"
# 	await context.bot.send_message(chat_id=update.effective_chat.id,
# 								   text=msg)
# 	return False
async def permissions(update: Update,
                      context: ContextTypes.DEFAULT_TYPE) -> str:
    # if await authenticate(update, context):
    text = (
        "You can grant or revoke access to this bot to a specific user or a specific chat.\n"
        "To abort, simply type /stop.")

    buttons = [
        [
            InlineKeyboardButton(text="Grant access",
                                 callback_data=str(GRANT_ACCESS)),
            InlineKeyboardButton(text="Revoke access",
                                 callback_data=str(REVOKE_ACCESS)),
        ],
        [
            InlineKeyboardButton(text="Done", callback_data=str(END)),
        ],
    ]
    keyboard = InlineKeyboardMarkup(buttons)

    # If we're starting over we don't need to send a new message
    if context.user_data.get(START_OVER):
        await update.callback_query.answer()
        await update.callback_query.edit_message_text(text=text,
                                                      reply_markup=keyboard)
    else:
        await update.message.reply_text(text=text, reply_markup=keyboard)

    context.user_data[START_OVER] = False
    return SELECTING_ACTION


async def permissions_grant(update: Update,
                            context: ContextTypes.DEFAULT_TYPE) -> str:
    await context.bot.send_message(chat_id=update.effective_chat.id,
                                   text="GRANT WIP")
    return GRANT_ACCESS


async def permissions_revoke(update: Update,
                             context: ContextTypes.DEFAULT_TYPE) -> str:
    await context.bot.send_message(chat_id=update.effective_chat.id,
                                   text="REVOKE WIP")
    return REVOKE_ACCESS


async def unknown(update: Update, context: ContextTypes.DEFAULT_TYPE):
    await context.bot.send_message(
        chat_id=update.effective_chat.id,
        text="Sorry, I didn't understand that command.",
    )


async def stop(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    """End Conversation by command."""
    await update.message.reply_text("Okay, bye.")

    return END


async def end(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    """End conversation from InlineKeyboardButton."""
    await update.callback_query.answer()

    text = "See you around!"
    await update.callback_query.edit_message_text(text=text)

    return END


if __name__ == "__main__":
    application = ApplicationBuilder().token(
        configuration.TELEGRAM_API_KEY).build()

    perm_handler = ConversationHandler(
        entry_points=[CommandHandler("permissions", permissions)],
        states={
            SHOWING:
            [CallbackQueryHandler(permissions, pattern="^" + str(END) + "$")],
            SELECTING_ACTION: [
                CallbackQueryHandler(permissions_grant,
                                     pattern="^" + str(GRANT_ACCESS) + "$"),
                CallbackQueryHandler(permissions_revoke,
                                     pattern="^" + str(REVOKE_ACCESS) + "$"),
                CallbackQueryHandler(end, pattern="^" + str(END) + "$"),
            ],
            GRANT_ACCESS: [CommandHandler("permissions", permissions)],
			REVOKE_ACCESS: [CommandHandler("permissions", permissions)],
        },
        fallbacks=[CommandHandler("stop", stop)],
    )
    application.add_handler(perm_handler)

    unknown_handler = MessageHandler(filters.COMMAND, unknown)
    application.add_handler(unknown_handler)

    application.run_polling()
